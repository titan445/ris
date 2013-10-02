#pragma once
/* 
 * File:   UdpBroatcast.cpp
 * Author: vfs
 * 
 * Created on 29 Сентябрь 2013 г., 1:23
 */

#include "UdpBroatcast.h"

UdpBroatcast::UdpBroatcast(boost::asio::io_service& io_service,
        udp::endpoint& listenAddress, string idStr) :
udp_server(io_service, listenAddress, idStr) {
}

void UdpBroatcast::send() {
    udp::endpoint receiver_endpoint = udp::endpoint(boost::asio::ip::address_v4::broadcast(), PORT_BROATCAST);
    boost::shared_ptr<std::string> message(
            new std::string("send message\n"));

    socket_.async_send_to(boost::asio::buffer(*message), receiver_endpoint,
            boost::bind(&UdpBroatcast::handle_send, this, message,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
}

void UdpBroatcast::handle_receive(const boost::system::error_code& error,
        std::size_t bytes_transferred) {
    cout << remote_endpoint_ << endl;
    if (!error || error == boost::asio::error::message_size) {
        boost::shared_ptr<std::string> message(
                new std::string("dsdsad\n"));

        boost::system::error_code myError;

        boost::asio::ip::address_v4 curentHostIP =
                boost::asio::ip::address_v4::from_string("192.168.89.132");


        boost::asio::ip::address_v4 targetIP = 
                boost::asio::ip::address_v4::from_string("192.168.89.133"); // Configure output IP address. HACKHACK--Hardcoded for Debugging

        boost::asio::ip::udp::endpoint myEndpoint; // Create endpoint on specified IP.
        myEndpoint.address(targetIP);
        myEndpoint.port(PORT_LISTEN);
        cout << "curentHostIP" << curentHostIP << endl;
        if (remote_endpoint_.address() != curentHostIP) {
            cout << "curentHostIP="<<  curentHostIP << endl;
            cout << "remote_endpoint_.address()="<<  remote_endpoint_.address() << endl;
            
            std::cout << "send data to clients....." << endl;
            boost::asio::io_service io_service;

            udp_client client(io_service);

            string g = "test ";
            client.send(g, myEndpoint);

            cout << "test" << endl;
            //client.start_receive();
            //cout << "test1"<<endl;
            //io_service.run();
            cout << "Send client complitefd" << endl;

            cerr << "handle receive " << id << "\n" << endl;
        }
        start_receive();
    }
}

void UdpBroatcast::handle_send(boost::shared_ptr<std::string> message,
        const boost::system::error_code& error,
        std::size_t bytes_transferred) {

}

UdpBroatcast::~UdpBroatcast() {

}