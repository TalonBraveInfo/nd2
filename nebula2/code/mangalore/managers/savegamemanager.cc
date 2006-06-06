//------------------------------------------------------------------------------
//  game/savegamemanager.cc
//  (C) 2005 Radon Labs GmbH
//------------------------------------------------------------------------------
#include "managers/savegamemanager.h"
#include "loader/server.h"
#include "managers/setupmanager.h"
#include "managers/entitymanager.h"
#include "kernel/nfileserver2.h"
#include "db/server.h"
#include "db/query.h"
#include "attr/attributes.h"
#include "game/server.h"
#include "application/app.h"
#include "application/statehandler.h"

namespace Managers
{
ImplementRtti(Managers::SaveGameManager, Game::Manager);
ImplementFactory(Managers::SaveGameManager);

SaveGameManager* SaveGameManager::Singleton = 0;

//------------------------------------------------------------------------------
/**
*/
SaveGameManager::SaveGameManager()
{
    n_assert(0 == Singleton);
    Singleton = this;
}

//------------------------------------------------------------------------------
/**
*/
SaveGameManager::~SaveGameManager()
{
    n_assert(Singleton);
    Singleton = 0;
}

//------------------------------------------------------------------------------
/**
    This method get the world database.
*/
nString
SaveGameManager::GetWorldDb()
{
    if (this->overrideWorldDb.IsValid())
    {
        // override database set, use this
        return nString("db:") + this->overrideWorldDb;
    }
    else
    {
        // return default database
        return nString("db:world.db3");
    }
}

//------------------------------------------------------------------------------
/**
    This method queries the world database for the startup level.
*/
nString
SaveGameManager::QueryStartupLevel()
{
    if (this->overrideStartLevel.IsValid())
    {
        // override level set, use this
        return this->overrideStartLevel;
    }
    else
    {
        // query the world database
        nString sql;
        sql.Format("SELECT * FROM _Entities WHERE _Type='TEMPLATE' AND _Category='.Levels' AND StartLevel='true'");
        Ptr<Db::Query> query = Db::Server::Instance()->CreateQuery(sql);
        query->Execute();
        if (query->GetNumRows() > 0)
        {
            return query->GetAttr(Attr::Id, 0).GetString();
        }
        else
        {
            n_error("No start level defined!\nCheck db/levels.xml and do a complete batchexport!");
            return "";
        }
    }
}

//------------------------------------------------------------------------------
/**
    This method starts a new game by creating a copy of the initial
    world database into the current user profile's directory. This copy is
    the mutable world database where is game is played from. After the copy
    has been created, SetupManager::SetupWorldFromLevel() will be called with
    the given initialLevel.
*/
bool
SaveGameManager::NewGame()
{
    nFileServer2* fileServer = nFileServer2::Instance();
    Loader::UserProfile* userProfile = Loader::Server::Instance()->GetUserProfile();
    Db::Server* dbServer = Db::Server::Instance();
    Application::StateHandler* curAppStateHandler = Application::App::Instance()->GetCurrentStateHandler();
    n_assert(curAppStateHandler);

    // close database before it will be deleted
    if (dbServer->IsOpen())
    {
        dbServer->Close();
    }

    fileServer->MakePath(userProfile->GetProfileDirectory());
    nString dbPath = userProfile->GetDatabasePath();
    if (fileServer->FileExists(dbPath))
    {
        fileServer->DeleteFile(dbPath);
    }
    fileServer->CopyFile(this->GetWorldDb(), dbPath);

    // open database with new file
    dbServer->SetDatabaseFilename(dbPath);
    dbServer->Open();

    // notify application state handler
    curAppStateHandler->OnLoadBefore();

    // setup the world
    SetupManager* setupManager = SetupManager::Instance();
    nString startupLevel = this->QueryStartupLevel();
    setupManager->SetCurrentLevel(startupLevel);
    setupManager->SetupWorldFromCurrentLevel();

    // notify application state handler
    curAppStateHandler->OnLoadAfter();

    return true;
}

//------------------------------------------------------------------------------
/**
    Return true if a current game exists (created by NewGame()).
*/
bool
SaveGameManager::CurrentGameExists()
{
    nFileServer2* fileServer = nFileServer2::Instance();
    Loader::UserProfile* userProfile = Loader::Server::Instance()->GetUserProfile();
    return fileServer->FileExists(userProfile->GetDatabasePath());
}

//------------------------------------------------------------------------------
/**
    This method continues the game from the last known state (the existing
    world database file in the user profile's directory, created by StartNewGame().
    The method will fail hard if a continue game is not possible
    (you can check this beforehand with the method CurrentGameExists()). The
    method will eventually call SetupManager::Instance()->SetupWorldFromLevel().
*/
bool
SaveGameManager::ContinueGame()
{
    n_assert(this->CurrentGameExists());
    Db::Server* dbServer = Db::Server::Instance();
    Application::StateHandler* curAppStateHandler = Application::App::Instance()->GetCurrentStateHandler();
    n_assert(curAppStateHandler);

    // re-open db server
    if (dbServer->IsOpen())
    {
        dbServer->Close();
    }
    Loader::UserProfile* userProfile = Loader::Server::Instance()->GetUserProfile();
    dbServer->SetDatabaseFilename(userProfile->GetDatabasePath());
    dbServer->Open();

    // notify application state handler
    curAppStateHandler->OnLoadBefore();

    // setup world
    SetupManager::Instance()->SetupWorldFromCurrentLevel();

    // notify application state handler
    curAppStateHandler->OnLoadAfter();

    return true;
}

//------------------------------------------------------------------------------
/**
    Create a new savegame. This will flush all unwritten data back to the
    database, and make a copy of the database.
*/
bool
SaveGameManager::SaveGame(const nString& saveGameName)
{
    nFileServer2* fileServer = nFileServer2::Instance();

    // flush unwritten data back to database
    Game::Server::Instance()->Save();

    // create a copy of the current world database
    Loader::UserProfile* userProfile = Loader::Server::Instance()->GetUserProfile();
    fileServer->MakePath(userProfile->GetSaveGameDirectory());
    nString dbPath = userProfile->GetDatabasePath();
    nString saveGamePath = userProfile->GetSaveGamePath(saveGameName);
    if (fileServer->FileExists(saveGamePath))
    {
        fileServer->DeleteFile(saveGamePath);
    }
    fileServer->CopyFile(dbPath, saveGamePath);
    return true;
}

//------------------------------------------------------------------------------
/**
    Load a saved game. This will overwrite the current world database
    with the saved game database file then call
    SetupManager::SetupWorldFromCurrentLevel(). If the savegame file
    doesn't exist the method returns false and nothing will change.
*/
bool
SaveGameManager::LoadGame(const nString& saveGameName)
{
    Loader::UserProfile* userProfile = Loader::Server::Instance()->GetUserProfile();
    nFileServer2* fileServer = nFileServer2::Instance();
    Application::StateHandler* curAppStateHandler = Application::App::Instance()->GetCurrentStateHandler();
    n_assert(curAppStateHandler);

    // get relevant filenames
    nString dbPath  = userProfile->GetDatabasePath();
    nString saveGamePath = userProfile->GetSaveGamePath(saveGameName);

    // check if savegame file exists
    if (!fileServer->FileExists(saveGamePath))
    {
        return false;
    }

    // close and delete old database, copy, open new database
    Db::Server* dbServer = Db::Server::Instance();
    if (dbServer->IsOpen())
    {
        dbServer->Close();
    }
    if (fileServer->FileExists(dbPath))
    {
        fileServer->DeleteFile(dbPath);
    }
    fileServer->CopyFile(saveGamePath, dbPath);
    dbServer->SetDatabaseFilename(dbPath);
    dbServer->Open();

    // notify application state handler
    curAppStateHandler->OnLoadBefore();

    // setup world from saved game
    SetupManager::Instance()->SetupWorldFromCurrentLevel();

    // notify application state handler
    curAppStateHandler->OnLoadAfter();

    return true;
}

}; // namespace Game
