//
// Copyright (c) 2018 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/vinniefalco/CppCon2018
//
#include <iostream>
#include <map>
#include "shared_state.h"
#include "websocket_session.h"
#include "algValidator.h"
//#include "jwt.h"
#include "verifyObj.h"
shared_state::
shared_state(std::string doc_root)
    : doc_root_(std::move(doc_root))
{
    //std::cout<<"newRegistrationRequest: "<<this->keys.newRegistrationRequest<<std::endl;
}

void
shared_state::
join(websocket_session& session)
{
    std::cout << "in sharedstate::join add session to sessions" << std::endl;

    sessions_.insert(&session);
}

void
shared_state::
leave(websocket_session& session)
{
    //*********** Session Managment Code Started **************//    
    
    sessions_.erase(&session);
    //*********** Session Managment Code Ended **************//
}

Message
shared_state::
leftSession(websocket_session& session)
{
    auto clientvalue = (&session)->clientvalue;
    auto usernameValue = (&session)->username;
    Message clientMsg;
    for (ClientIt=ClientCounter.begin(); ClientIt!= ClientCounter.end();ClientIt++)
    {
        if (ClientIt->first == clientvalue)
        
            {
                ClientIt->second --;
                if (ClientIt->second == 0)
                {
                    std::string msg = "";
                    const char* value = msg.c_str();
                   // clientMsg.clientDoc = std::move(value);
                    ClientCounter.erase(ClientIt);
                    this->lastSessionFlag = true;
                    break;
                }
                else break;
            }
    }
    return std::move(clientMsg);    
}


void
shared_state::
send(std::string message)   
{
    std::cout << "in shared_state_send with message: " << message << std::endl;
    auto const ss = std::make_shared<std::string const>(std::move(message));
    for (auto session : sessions_)
        session->send(ss);
}

bool 
shared_state::
FirstClientLogin(std::string clientvalue)
{    
    bool FirstConnection=true;
    for (ClientIt=ClientCounter.begin(); ClientIt!= ClientCounter.end();ClientIt++)
    {
        if (ClientIt->first == clientvalue)
            {
                FirstConnection = false;
                ClientIt->second ++;
                break;
            }
    }
    if (FirstConnection)
            ClientCounter.insert(std::pair<std::string,int>(clientvalue,1));
    return FirstConnection;
}

int 
shared_state::
mapClients(const char* clientDoc){

    bool auth=false;
    std::string action="";
    if(true){
        auth =true;
    }

    return auth;
}

websocket_session*
shared_state::
checkIfDuplicateSession(websocket_session* session, const char* clientDoc, bool& duplicateSession)
{   
    websocket_session* ss;
    std::string clientUserName= "";//this->keys.getUsernameValue(clientDoc)+this->keys.getClientValue(clientDoc);       
    std::string action = "";//this->keys.getActionValue(clientDoc);
    if (true)
    {
        for (it =sessions_.begin(); it!=sessions_.end(); it++)
        {
                            if ((*it)->username == clientUserName)
                                {
                                    if (session == (*it))
                                        continue;
                                    else{
                                        duplicateSession = true;
                                        ss = (*it);
                                        break;
                                    }
                                }
        }

    }
    return ss;
}

void
shared_state::
addClientContents(websocket_session& session,const char* clientDoc){
    std::string action="";//this->keys.getActionValue(clientDoc);
    std::string clientValue= "";//this->keys.getClientValue(clientDoc);
    std::string clientUserName= "";//this->keys.getUsernameValue(clientDoc)+clientValue;       
    //std::string JWTToken = this->keys.getJWTTokenValue(clientDoc);
    
    if ((*(sessions_.find(&session)))->useridentified == false)
    {
        (*(sessions_.find(&session)))->username = clientUserName;
        (*(sessions_.find(&session)))->clientvalue = clientValue;
        (*(sessions_.find(&session)))->action = action;
        (*(sessions_.find(&session)))->useridentified = true;
        //(*(sessions_.find(&session)))->JWT = JWTToken;
    }   
    else if((*(sessions_.find(&session)))->username != clientUserName){
        (*(sessions_.find(&session)))->username = clientUserName;
        (*(sessions_.find(&session)))->clientvalue = clientValue;
        //check if the user is authorised
    }
}

void 
shared_state::
authResponse(){//std::string client,bsoncxx::builder::basic::document response){
//    std::cout<<"in auth response"<<std::endl;
//   ALGValidator signer("HS256", EVP_sha256(), this->raaz);
//    auto payload =JWT::createPayload(response.view(),this->expiry,this->keys);
//    std::cout<<"payload: "<<std::endl;
//    std::cout<<bsoncxx::to_json(payload.view())<<std::endl;
//    auto header=JWT::createHeader();
//    std::cout<<"header: "<<std::endl;
//    std::cout<<bsoncxx::to_json(header.view())<<std::endl;
//    auto token = JWT::Encode(signer, payload.view(), header.view());
//    std::cout<<"token: "<<std::endl;
//    std::cout<<token<<std::endl;

//    response.append(bsoncxx::builder::basic::kvp(this->keys.jwtKey, token));
//    this->sendToClient(client,bsoncxx::to_json(response.view()));
}

/*void 
shared_state::
sendToClient(std::string client,bsoncxx::builder::basic::document doc){
    //websocket_session clientSession;
    try{
        bool userNameExist = false;
        this->keys.print("respMsg: ", doc.view());
        auto respMsg=this->keys.getActionValue(doc);
        std::cout<<"sendToClient resMsg: "<< respMsg<<std::endl;
        if (keys.authResponseSuccess.compare(respMsg)==0|| this->keys.newRegistrationSuccessful.compare(respMsg) == 0){
            std::cout<<"move doc onto authResponse object"<<std::endl;
            this->authResponse(client,std::move(doc));
            std::cout<<"doc moved to authResponse object"<<std::endl;
        }
        else if(keys.authResponseFailure.compare(respMsg)==0||keys.newRegistrationFailed.compare(respMsg)==0){
            //remove client from shared state and disconnect
            
            
            //*********** Session Managment Code Started **************
            auto const ss = std::make_shared<std::string const>(std::move(bsoncxx::to_json(doc.view())));            
            for (it =sessions_.begin(); it!=sessions_.end(); it++)
            {
                if ((*it)->username != "")
                {
                    userNameExist = true;
                    if ((*it)->username == client)
                    {
                        break;
                    }
                }
                else 
                    userNameExist = false;
            }
            if (userNameExist)
                (*it)->send(ss);
            else
                throw std::invalid_argument("userName not found");
            //*********** Session Managment Code Ended **************
        }
        else{
            std::cout<<"in else line 156"<<std::endl;         
            auto const ss = std::make_shared<std::string const>(std::move(bsoncxx::to_json(doc.view())));
            //*********** Session Managment Code Started **************
            for (it =sessions_.begin(); it!=sessions_.end(); it++)
            {
                if ((*it)->username != "")
                {
                    userNameExist = true;
                    if ((*it)->username == client)
                        break;

                }
                else userNameExist = false;
            }
            if (userNameExist)
                (*it)->send(ss);
            else
                throw std::invalid_argument("userName not found");

            //*********** Session Managment Code Ended **************
        }
    }
    catch(const std::invalid_argument& e){
        bool userNameExist = false;
        std::cout << e.what() << std::endl;
        auto reply = "{\"action\":\"msgFormatError\",\"msg\":{\"reason\":\"response message could not be read\"}}";
        auto const ss = std::make_shared<std::string const>(std::move(reply));
            //*********** Session Managment Code Started **************
            for (it =sessions_.begin(); it!=sessions_.end(); it++)
            {
                if ((*it)->username != "")
                {
                    userNameExist = true;
                    if ((*it)->username == client)
                        break;

                }
                else
                    userNameExist = false;
            }
            if (userNameExist)
                (*it)->send(ss);
            else
                throw std::invalid_argument("userName not found");

                //*********** Session Managment Code Ended **************
    }
    catch(const std::runtime_error& e){
        bool userNameExist = false;
        std::cout << e.what() << std::endl;
        auto reply = "{\"action\":\"msgFormatError\",\"msg\":{\"reason\":\"response message could not be read\"}}";
        auto const ss = std::make_shared<std::string const>(std::move(reply));
        //*********** Session Managment Code Started **************
        for (it =sessions_.begin(); it!=sessions_.end(); it++)
            {
                if ((*it)->username != "")
                {
                    userNameExist = true;
                    if ((*it)->username == client)
                        break;
                }
                else
                    userNameExist = false;

            }

            if (userNameExist)
                (*it)->send(ss);
            else
                throw std::invalid_argument("userName not found");

            //*********** Session Managment Code Ended **************
    }
    catch(const std::exception& e){
        bool userNameExist = false;
        std::cout << e.what() << std::endl;
        bool sessionFound;
        auto reply = "{\"action\":\"msgFormatError\",\"msg\":{\"reason\":\"response message could not be read\"}}";
        auto const ss = std::make_shared<std::string const>(std::move(reply));
        //*********** Session Managment Code Started **************
            for (it =sessions_.begin(); it!=sessions_.end(); it++)
            {
                if ((*it)->username != "")
                {
                    userNameExist = true;
                    if ((*it)->username == client)
                        break;

                }
            else
                userNameExist = false;

            }
            if (userNameExist)
                (*it)->send(ss);
            else
                throw std::invalid_argument("userName not found");

        //*********** Session Managment Code Ended **************
    }    
}
*/
void 
shared_state::
sendToClient(std::string client,std::string message){
    //*********** Session Managment Code Started **************//
    //websocket_session clientSession;
    bool userNameExist = false;
    std::cout<<"int send to client string edition"<<std::endl;
    auto const ss = std::make_shared<std::string const>(std::move(message));
    
    
    std::cout<<"**********sendToClientStringEdition sessionlist begin**********"<<std::endl;
    for (auto it =sessions_.begin(); it!=sessions_.end(); it++){
        if((*it)->useridentified){
            std::cout<<"current session username: "<<(*it)->username<<std::endl;
        }
        else{
            std::cout<<"user not identified"<<std::endl;
        }
    }
    std::cout<<"**********sendToClientStringEdition sessionlist end***********"<<std::endl;
    
    for (it =sessions_.begin(); it!=sessions_.end(); it++)
            {
                if ((*it)->username != "")
                {
                    userNameExist = true;
                    if ((*it)->username == client)
                        break;

                }
            else
                userNameExist = false;

            }
            if (userNameExist)
                (*it)->send(ss);
            else
                throw std::invalid_argument("userName not found");

    //*********** Session Managment Code Ended **************//
}

void 
shared_state::
sendToClient(std::string client,std::shared_ptr<std::string const> const& ss){
    //*********** Session Managment Code Started **************//
    bool userNameExist = false;
    std::cout<<"int send to client sharedptr edition"<<std::endl;
    std::cout<<"client "<<client<<std::endl;
    std::cout<<"**********sendToClientsharedptr sessionlist begin**********"<<std::endl;
    for (auto it =sessions_.begin(); it!=sessions_.end(); it++){
        if((*it)->useridentified){
            std::cout<<"username: "<<(*it)->username<<std::endl;
        }
        else{
            std::cout<<"user not identified"<<std::endl;
        }
    }
    std::cout<<"**********sendToClientsharedptr sessionlist end***********"<<std::endl;


    for (it =sessions_.begin(); it!=sessions_.end(); it++)
        {
            if ((*it)->username != "")
            {
                userNameExist = true;
                if ((*it)->username == client)
                    break;

            }
            else
                userNameExist = false;

        }
        if (userNameExist)
            (*it)->send(ss);    
            else
                throw std::invalid_argument("userName not found");

    //*********** Session Managment Code Ended **************//

}

void shared_state::
addToSendQueue(std::string client, std::string message){
    //websocket_session clientSession;
    bool userNameExist = false;
    std::cout<<"int send to client string edition"<<std::endl;
    auto const ss = std::make_shared<std::string const>(std::move(message));
    //*********** Session Managment Code Started **************//    
    for (it =sessions_.begin(); it!=sessions_.end(); it++)
            {
                if ((*it)->username != "")
                {
                    userNameExist = true;
                    if ((*it)->username == client)
                        break;

                }
                else
                    userNameExist = false;
            }
            if (userNameExist)
                (*it)->send(ss);
            else
                throw std::invalid_argument("userName not found");

    //*********** Session Managment Code Ended **************//

}


void 
shared_state::
initiateSend(){
 std::cout<<"in initiate send, msg to be sent "<<std::endl;
}



void
shared_state::
addMsgToReceivedMsgQueue(Message clientMsg){
    this->newMsgMut.lock();
    this->receivedMsgQueue_.push(std::move(clientMsg));
    this->newMsgMut.unlock();
    this->newMsgReceivedCond.notify_one();
}



Message
shared_state:: 
getMsgFromReceivedMsgQueue(){
    //std::lock_guard<std::mutex> addMsgMut(this->newMsgMut);
    Message clientMsg= std::move(this->receivedMsgQueue_.front());
    this->receivedMsgQueue_.pop();
    return std::move(clientMsg);
}

int
shared_state:: 
getReceivedMsgQueueSize(){
    return this->receivedMsgQueue_.size();
}

int 
shared_state::
getToSendMsgQueueSize(std::string client){
    //*********** Session Managment Code Started **************//
    bool userNameExist = false;
    for (it =sessions_.begin(); it!=sessions_.end(); it++)
    {
        if ((*it)->username != "")
        {
            userNameExist = true;
            if ((*it)->username == client)
                break;
        }
        else
            userNameExist = false;
    }
    if (userNameExist)
        return (*it)->getToSendQueueSize();
    else
        throw std::invalid_argument("userName not found");

    //*********** Session Managment Code Ended **************//
}

void 
shared_state::
sendMessageFromQueue(std::string client){
    //*********** Session Managment Code Started **************//
    bool userNameExist = false;
    for (it =sessions_.begin(); it!=sessions_.end(); it++)
    {
        if ((*it)->username != "")
        {
            userNameExist = true;
            if ((*it)->username == client)
                break;
        }
        else
            userNameExist = false;
    }
    if (userNameExist)
        (*it)->sendFrontMsg();
    else
        throw std::invalid_argument("userName not found");

    //*********** Session Managment Code Ended **************//
}

void 
shared_state::
sendMessageFromAllQueues(){
    //*********** Session Managment Code Started **************//
    for (it =sessions_.begin(); it!=sessions_.end(); it++)
    {
        std::cout<<"queue size "<<(*it)->getToSendQueueSize()<<std::endl;
        if((*it)->getToSendQueueSize()>0){
            (*it)->sendFrontMsg();
        }
    }
    //*********** Session Managment Code Ended **************//
}

void shared_state::lockReceivedMsgMutex(){
    {
        std::lock_guard<std::mutex> guard(this->newMsgMut);
    }

}