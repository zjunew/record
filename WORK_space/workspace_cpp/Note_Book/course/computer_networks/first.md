* ISP全称：Internet Service Provider，中文名叫互联网服务提供商，
指的是提供互联网接入服务的单位。如中国电信、中国联通等互联网运
营单位及其在各地的分支机构和下属的组建局域网的专线单位。
* 常见的stateless协议有HTTP和DNS
>Stateless protocol的优点是简单、易于实现和扩展，但缺点是无法保存会话状态，
需要在每次请求中重新传输所有必要的信息，可能会造成额外的开销。因此，在某些情况下，会采用一些方法来维护状态，例如在HTTP中使用cookie或session来保存会话状态。

## 使用TCP协议
SMTP         电子邮件  
TELNET       远程终端接入  
HTTP         万维网  
FTP          文件传输  

## 使用UDP协议
DNS          域名转换  
TFTP         文件传输  
SNMP         网络管理  
NFS          远程文件服务器  

* PoP就是在提供商网络中同一个地方的一组路由器（不少于1台），客户ISP就通过这组路由器与提供商ISP相连。

### 介绍SMTP、IMAP、POP三种邮件协议及其功能点
https://blog.csdn.net/qq_44852846/article/details/120716611

