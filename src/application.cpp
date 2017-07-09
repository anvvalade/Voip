#include "application.h"
#include "windows.h"

Application::Application() : QObject(), mainwindow(this), connectionwindow(this), cryptowindow(this)
{
  connect(&udpsocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(connectionFailed(QAbstractSocket::SocketError)));
  connect(&udpsocket, SIGNAL(connected()), &connectionwindow, SLOT(close()));
//  connect(udp_socket, SIGNAL(connected()), this, SLOT(emitconnectionSucceeded));   
}

void Application::sendMessage()
{

}

void Application::attemptConnectToHost()
{ 
  if (!hostaddress.setAddress(connectionwindow.le_hostaddress->text())) 
  {
    alertwindow.setMessage("Host Address not understood...");
    alertwindow.show();
    return;
  }
  bool ok;
  port = connectionwindow.le_port->text().toInt(&ok);
  if (!ok) 
  {
    alertwindow.setMessage("Port not understood...");
    alertwindow.show();
    return;
  }
  udpsocket.connectToHost(hostaddress, port);
}

void Application::connectionFailed(QAbstractSocket::SocketError SErr)
{
  alertwindow.setMessage("Connection Failed... : " + socketerrorname(SErr));
  alertwindow.show();
}
