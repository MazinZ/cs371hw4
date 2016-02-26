#include <iostream>      /* for printf() and fprintf() */
#include <sys/socket.h> /* for recv() and send() */
#include <unistd.h>     /* for close() */
#include <cstring>
#include "string.h"
#include <fstream>
#include <vector>
#include <sstream>


using namespace std;

#define RCVBUFSIZE 10000   /* Size of receive buffer */
#define HEADERSIZE 100000

void DieWithError(char *errorMessage);  /* Error handling function */

vector<string> parser(string s);
string getFiletype(string path);
string getContentType(string fileType);
string int_to_str(int i);

void HandleTCPClient(int clntSocket)

{
    char echoBuffer[RCVBUFSIZE];        /* Buffer for echo string */
    int recvMsgSize;                    /* Size of received message */
    
    
    /* Receive message from client */
    if ((recvMsgSize = recv(clntSocket, echoBuffer, RCVBUFSIZE, 0)) < 0)
        DieWithError("recv() failed");
        
    //char requestType[4];
    //memcpy(requestType, &echoBuffer, 3);
    
    //requestType[4] = '\0';
    int charCounter = 0;
    
    ifstream myfile ("./profilepicture.png", ios_base::binary);
    string line;
    string fullfile = "";
    
    string requestStr = echoBuffer;
    vector<string> parsed;
    parsed = parser(requestStr);
    
    
    FILE *fp;
    char * headerBuffer;
    char fileBuff[100000];
    string filePath;
    int length;
    
    if (parsed[1]!="/") {
        filePath = "." + parsed[1];
    }
    else {
        filePath = "./index.html";
    }
    
    string headerString;
    
    //fp = fopen ("./deadfish2.gif", "r");
    fp = fopen(filePath.c_str(),"r");
    if (fp != NULL)
    {
        ifstream is;
        is.open (filePath.c_str(), ios::binary );
        is.seekg (0, ios::end);
        length = is.tellg();
        is.close();
        
        
 
     
        cout << "testing" << endl;
        headerString = "HTTP/1.0 200 OK\r\nContent-Type:" + getContentType(getFiletype(filePath)) + "\r\nContent-Length:" + int_to_str(length) + "\r\n\r\n";
        cout << "Headstr: " << headerString << endl;
          
        cout << headerString.length() << endl;
        headerBuffer = new char[headerString.length()+1+length];
        cout << "Size of" << strlen(headerBuffer) << endl;
        cout << headerBuffer << endl;
        fread(headerBuffer, sizeof(char), length+1, fp);
        fclose(fp);
        

        
    }
    else {
        cout << "testing2" << endl;
       // strcpy(headerBuffer, response.c_str());
        fp = fopen ("./404.html", "r");
        strcpy(headerBuffer, "HTTP/1.0 404 Not Found\r\nContent-Type:text/html\r\n");
        fread(headerBuffer, sizeof(char), 182, fp);
        fclose(fp);
        // Add 404 not found response here
    }
    
      
    
    ///////////////////// Todo: Check against lowercase get
   
    if (parsed[0] != "GET"){
        cout << "Request type: " <<  parsed[0] << endl;
        DieWithError("Only GET requests are allowed");
        
        }
    
    else {
        
        //if (send(clntSocket, responseBuffer, recvMsgSize, 0) != recvMsgSize)
            //DieWithError("send() failed");
            for (int i = 0; i<parsed.size(); i++) {
                cout << parsed[i] << endl;
            }
            if (headerBuffer == NULL){
                cout << "headerbuffer is nULL" << endl; 
            }
            send(clntSocket, headerBuffer, headerString.length()+1+length, 0);
            //send(clntSocket, fileBuff, sizeof(fileBuff), 0);
        
    }
   
  
        
    close(clntSocket);    /* Close client socket */
}



vector<string> parser(string s) {
    vector<string> parsed;
    int i = 0;
    int j = 0;
    replace(s.begin(),s.end(), '\t', ' ');
    string token = s.substr(0, s.find(" "));
    size_t pos = 0;
    string delimiter = " ";
    while ((pos = s.find(delimiter)) != s.length()+1 && parsed.size()!=2) {
        token = s.substr(0, pos);
            if (token != "") {
            parsed.push_back(token);
            }
            s.erase(0, pos + (delimiter).length());
    }
    return parsed;
}


string getFiletype(string path) {
    string possibleFormats[] =  {".jpg", ".html",".txt",".gif"};

    size_t found = path.find_last_of(".");
    string contentType = "";
    if (found == string::npos){
        return "";
    }
    else {
        contentType = path.substr(found, path.length());
        for (int i = 0; i < 4; i++){
            if (contentType == possibleFormats[i])
                return contentType;
        }
        return "";
        
    }
    return contentType;
}

string getContentType(string fileType) {
    if (fileType == ".jpg")
        return "image/jpg";
    else if (fileType == ".gif")
        return "image/gif";
    else if (fileType == ".txt")
        return "text/plain";
    else if (fileType == ".html")
        return "text/html";
    else
        return "";
}

string int_to_str(int i){
    stringstream ss;
    ss << i;
    string str = ss.str();
    return str;
}

