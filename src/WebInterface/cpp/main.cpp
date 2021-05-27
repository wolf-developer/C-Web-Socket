#include <iostream>
#include "webInterface.h"
#include "algValidator.h"
#include "listener.h"
#include <set>
#include <queue>

int main(){

    WebInterface webInterface;
       net::io_context ioc;
    


  //create the ssl context
    boost::asio::ssl::context context_{boost::asio::ssl::context::sslv23};
   //*********SET SSL CONTEXT OPTIONS***************
    context_.set_options(
        boost::asio::ssl::context::default_workarounds
        | boost::asio::ssl::context::no_sslv2
        | boost::asio::ssl::context::no_sslv3
        | boost::asio::ssl::context::single_dh_use);

    //*****************************************************

    //set ssl certificate paths
    //context_.set_password_callback(boost::bind(&server::get_password, this));
    
    //local path
    //context_.use_certificate_chain_file("/home/arif/Documents/certificates/abstraca_cert_chain.crt");
    //context_.use_private_key_file("/home/arif/Documents/certificates/app_abstraca.key", boost::asio::ssl::context::pem);
    
    //server path
    context_.use_certificate_chain_file("/usr/certs/abstract_london_chain.crt");
    context_.use_private_key_file("/usr/certs/abstract_london_key.key", boost::asio::ssl::context::pem); 
//    context_.use_certificate_chain_file("/home/arifsaeed78/abstract_london_chain.crt");
//    context_.use_private_key_file("/home/arifsaeed78/abstract_london_key.key", boost::asio::ssl::context::pem); 




    // Create and launch a listening port
    std::make_shared<listener>(
        ioc,
        tcp::endpoint{ webInterface.address, webInterface.port },
        webInterface.shst,
        context_)->run();
        //std::make_shared<shared_state>(doc_root))->run();

    // Capture SIGINT and SIGTERM to perform a clean shutdown
    net::signal_set signals(ioc, SIGINT, SIGTERM);
    signals.async_wait(
        [&ioc](boost::system::error_code const&, int)
        {
            // Stop the io_context. This will cause run()
            // to return immediately, eventually destroying the
            // io_context and any remaining handlers in it.
            ioc.stop();
        });

    // Run the I/O service on the main thread
    std::thread thread1{[&ioc](){ ioc.run(); }};
    int threadIndex;

    //**************OLD RESPONSE DOC WITH STRING*******************
    //std::vector<std::string> responseDocs;
    //**************OLD RESPONSE DOC WITH STRING*******************

    std::vector<std::string> responseClients;

 
    std::cout<<"starting infinite loop"<<std::endl;
    bool running = true;
    int count=0;
    int size;
    std::cout<<"running: " <<size<<std::endl;

    while(running){
        size = webInterface.shst->getReceivedMsgQueueSize();

    }
    //****************************JWT TEST*************************************************
    /*
    std::string origtoken = "eyAiQWxnIiA6ICJyc2EiLCAidHlwIiA6ICJKV1QiIH0.eyAidXNlcnR5cGUiIDogImFkbWluIiwgInByb2ZpbGUiIDogWyAgXSB9.yyIbseUMAVTe3G36uVIPOsLdv_9ugntn81aA157Ip9c";
    std::string token = "eyAiQWxnIiA6ICJyc2EiLCAidHlwIiA6ICJKV1QiIH0.eyAidXNlcnR5cGUiIDogImFkbWluIiwgInByb2ZpbGUiIDogWyAgXSB9.yyIbseUMAVTe3G36uVIPOsLdv_9ugntn81aA157Ip9c";

    JWT jwt;

    auto result = jwt.Decode(token.c_str(),token.size());

    std::cout<<"header0: "<<bsoncxx::to_json(std::get<0>(result).view())<<std::endl; 
    std::cout<<"header1: "<<bsoncxx::to_json(std::get<1>(result).view())<<std::endl; 
     std::cout<<"wi"<<std::endl;
    std::string origkey="XcRodEs!£dlpWLKjdO9873";
    std::string key="xcRodEs!£dlpWLKjdO9873";
    ALGValidator signer("HS256", EVP_sha256(), key);
//    nlohmann::json payload = {{"sub", "subject"}, {"exp", 1599316982}};
//    nlohmann::json header ={};
    //header["typ"] = "JWT";   implement this in calling function
    //header["alg"] = validator.algorithm_;    
    auto tokencheck = JWT::Encode(signer, std::get<1>(result).view(), std::get<0>(result).view());
    std::cout<<token<<std::endl;
    std::cout<<tokencheck<<std::endl;
    std::cout<<token.compare(tokencheck)<<std::endl;
//    std::cout << token << std::endl;
    */
}