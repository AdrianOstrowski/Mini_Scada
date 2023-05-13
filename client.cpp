#include "client.h"

Client::Client(std::string ip, unsigned short port)
{
    this->ip = ip;
    this->port = port;
}

Client::~Client()
{
    delete socket;
}


bool Client::start()
{

}

bool Client::connect_to_server()
{

    return 0;
}

bool Client::disconnect_from_server()
{

    return 0;
}

void Client::send_data(Data data)
{

}

void Client::recv_data()
{

}

void Client::save_data()
{

}

void Client::save_to_clipboard()
{

}

void Client::connected()
{

}

void Client::disconnected()
{

}

bool Client::closed()
{
    return true;
}
