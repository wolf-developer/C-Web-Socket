#include "webInterface.h"
//#include "jsonWriter.h"
//#include "document.h"

#include "listener.h"
#include "shared_state.h"
#include <boost/asio/signal_set.hpp>
#include <iostream>
#include <string>
#include <chrono>
#include <thread>

WebInterface::WebInterface( ){
    //char* rootptr, std::string strAdd,
    
    //********this is for local host*******************
    this->portNum =8060;
    //std::string strAdd = "0.0.0.0";
    std::string strAdd = "127.0.0.1";
    //********this is for local host*******************



    //**********this is for external IP****************
    //this->portNum =443;
    //std::string strAdd = "0.0.0.0";   
    //**********this is for external IP****************

    char root='.';
    char* rootptr=&root;
    address = net::ip::make_address(strAdd);
    //this->address = net::ip::make_address(strAdd);
    this->port = static_cast<unsigned short>(portNum);
    this->doc_root = rootptr;
    this->shst =std::make_shared<shared_state>(doc_root);
    
    

}

void WebInterface::run(){
    // The io_context is required for all I/O
    net::io_context ioc;
    
    //create the ssl context
    boost::asio::ssl::context context_{boost::asio::ssl::context::sslv23};
   //*********SET SSL CONTEXT OPTIONS***************
    context_.set_options(
        boost::asio::ssl::context::default_workarounds
        | boost::asio::ssl::context::no_sslv2
        | boost::asio::ssl::context::no_sslv3
        | boost::asio::ssl::context::single_dh_use);
    //context_.set_password_callback(boost::bind(&server::get_password, this));
    
    //context_.use_certificate_chain_file("/home/arif/Documents/certificates/app_abstraca.com/app_abstraca_com.ca-bundle");
    context_.use_certificate_chain_file("/home/arif/Documents/certificates/abstraca_cert_chain.crt");
    context_.use_private_key_file("/home/arif/Documents/certificates/app_abstraca.key", boost::asio::ssl::context::pem);


    // Create and launch a listening port
    std::make_shared<listener>(
        ioc,
        tcp::endpoint{ this->address, this->port },
        shst,
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

    thread1.join();
    //auto fut = std::async(ioc.run);
    //std::cout<<"IOC Started in thread: "<<std::endl;
    
    //receivedmsgqueue.receivedMsgs.push_back("this was written in main");
/*    
    //receivedMsg recMsg;
    int size=0;
    std::string returnMsg;
    std::chrono::milliseconds timespan(5000);
    auto clientDoc = bsoncxx::from_json("{}");
    while(1==1){
        std::this_thread::sleep_for(timespan);
        std::cout<<"in while loop"<<std::endl;
        size=shst->getReceivedMsgQueueSize();
        if (size>0){
            std::cout<<"size: "<<size<<std::endl;
            clientDoc=shst->getMsgFromReceivedMsgQueue();
            
            //returnMsg="{\"Action\":\"Authentication Failed\",\"JSON\":{\"userName\":\"" + recMsg.client + "\",\"from\":\"cpp server\"}}";
            //std::cout<<"returnMsg: "<<returnMsg<<std::endl;
            
            
            //****************************RETURN TO CLIENT*************************************
            //shst->sendToClient(recMsg.client,returnMsg);

        }
    }

    thread1.join();*/
    // (If we get here, it means we got a SIGINT or SIGTERM)

    //return EXIT_SUCCESS;
}