File fsUploadFile;

void fs_setup(){
  SPIFFS.begin();
  String sa;
  sa=F("/list"); server.on(sa.c_str(), HTTP_GET, handleFileList);
  sa=F("/edit");
  server.on(sa.c_str(), HTTP_GET, [](){ if(!handleFileRead("/edit.htm")) sendNotFound(); });
  server.on(sa.c_str(), HTTP_PUT, handleFileCreate);
  server.on(sa.c_str(), HTTP_DELETE, handleFileDelete);
  server.on(sa.c_str(), HTTP_POST, [](){ server.send(200, "text/plain", ""); }, handleFileUpload);
  server.on("/", HTTP_POST, [](){ server.send(200, "text/plain", ""); }, handleFileUpload);
  server.onNotFound( [](){ if(!handleFileRead(server.uri())) sendNotFound();} );
}

void handleFileList() {
  String sa,sb;
  sa=F("text/plain");
  sb=F("BAD ARGS"); if(!server.hasArg("dir")) { server.send(500, sa, sb); return; }
  String path = server.arg("dir");
  Dir dir = SPIFFS.openDir(path);  path = String();
  sa = "";
  String ano="", mes="", dia="", lgg="", outros="";
  while(dir.next()){
    File entry = dir.openFile("r");
    sa = String(entry.name()).substring(1);
    if( sa.startsWith("log/") ) { lgg+=sa; lgg += ","; } else
    if( sa.startsWith("dia/") ) { dia+=sa; dia += ","; } else
    if( sa.startsWith("mes/") ) { mes+=sa; mes += ","; } else
    if( sa.startsWith("ano/") ) { ano+=sa; ano += ","; } else { outros+=sa; outros += ","; }
    entry.close();
  }
  sa=ano+mes+dia+lgg+outros;
  //
  sb = "[";
  while(sa.indexOf(",")>=0){
    sb+=F("{\"type\":\"file\",\"name\":\"");
    sb += sa.substring(0,sa.indexOf(","));
    sb +=F("\"},");
    sa = sa.substring(sa.indexOf(",")+1);
  }
  if( sb.endsWith(",") ) sb=sb.substring(0,sb.length()-1);
  sb+="]";
  sa=F("text/json"); server.send(200, sa, sb);
}


bool handleFileRead(String path){
  if(path.endsWith("/")) path += F("index.htm");
  String contentType = getContentType(path);
  String pathWithGz = path + ".gz";
  if(SPIFFS.exists(pathWithGz) || SPIFFS.exists(path)){
    if(SPIFFS.exists(pathWithGz)) path += ".gz";
    File file = SPIFFS.open(path, "r");
    size_t sent = server.streamFile(file, contentType);
    file.close();
    return true;
  }
  return false;
}

void sendNotFound(){
  String sa,sb; sa=F("text/plain"); sb=F("FileNotFound");
  server.send(404, sa, sb);
}

void handleFileCreate(){
  String sa,sb;
  sa=F("text/plain");
  sb=F("BAD ARGS");     if(server.args() == 0) return server.send(500, sa, sb);
  String path = server.arg(0);
  //sb=F("handleFileCreate: "); DBG_OUTPUT_PORT.println(sb + path);
  sb=F("BAD PATH");     if(path == "/") return server.send(500, sa, sb);
  sb=F("FILE EXISTS");  if(SPIFFS.exists(path))    return server.send(500, sa, sb);
  File file = SPIFFS.open(path, "w");
  sb=F("CREATE FAILED");
  if(file)    file.close();  else    return server.send(500, sa, sb);
  server.send(200, sa, "");
  path = String();
}

void handleFileDelete(){
  String sa,sb;
  sa=F("text/plain"); sb=F("BAD ARGS");
  if(server.args() == 0) return server.send(500, sa, sb);
  String path = server.arg(0);
  sb=F("BAD PATH");     if(path == "/") return server.send(500, sa, sb);
  sb=F("FileNotFound"); if(!SPIFFS.exists(path)) return server.send(404, sa, sb);
  SPIFFS.remove(path);
  server.send(200, sa, "");
  path = String();
}

String getContentType(String filename){
  String sa,sb;
  sa=F("download"); sb=F("application/octet-stream"); if(server.hasArg(sa)) return sb;
  sa=F(".htm"); sb=F("text/html");                    if(filename.endsWith(sa)) return sb;
  sa=F(".html");                                      if(filename.endsWith(sa)) return sb;
  sa=F(".css"); sb=F("text/css");                     if(filename.endsWith(sa)) return sb;
  sa=F(".js"); sb=F("application/javascript");        if(filename.endsWith(sa)) return sb;
  sa=F(".png"); sb=F("image/png");                    if(filename.endsWith(sa)) return sb;
  sa=F(".gif"); sb=F("image/gif");                    if(filename.endsWith(sa)) return sb;
  sa=F(".jpg"); sb=F("image/jpeg");                   if(filename.endsWith(sa)) return sb;
  sa=F(".ico"); sb=F("image/x-icon");                 if(filename.endsWith(sa)) return sb;
  sa=F(".xml"); sb=F("text/xml");                     if(filename.endsWith(sa)) return sb;
  sa=F(".pdf"); sb=F("application/x-pdf");            if(filename.endsWith(sa)) return sb;
  sa=F(".zip"); sb=F("application/x-zip");            if(filename.endsWith(sa)) return sb;
  sa=F(".gz"); sb=F("application/x-gzip");            if(filename.endsWith(sa)) return sb;
  sb=F("text/plain"); return sb;
}

void handleFileUpload(){
  String sa,sb;
  sa=F("/edit"); sb=F("/upload"); 
  if((server.uri() != sa)&&(server.uri() != sb)&&(server.uri() != "/")) return;
  HTTPUpload& upload = server.upload();
  if(upload.status == UPLOAD_FILE_START){
    String filename = upload.filename;
    if(!filename.startsWith("/")) filename = "/"+filename;
    sa=F("handleFileUpload Name: ");
    fsUploadFile = SPIFFS.open(filename, "w");
    filename = String();
  } else if(upload.status == UPLOAD_FILE_WRITE){
    if(fsUploadFile)
      fsUploadFile.write(upload.buf, upload.currentSize);
  } else if(upload.status == UPLOAD_FILE_END){
    if(fsUploadFile) fsUploadFile.close();
  }
}

void fs_log_auto_del(String path, uint8_t maxFiles){
  FSInfo fs_info;
  SPIFFS.info(fs_info);
  fs_usedBytes=fs_info.usedBytes/1000;
  fs_totalBytes=fs_info.totalBytes/1000;
  Dir dir = SPIFFS.openDir(path);
  path=String();
  uint8_t n=0;
  String sa;
  while(dir.next()){
    n++;
    File entry = dir.openFile("r");
    sa=entry.name();
    if(path.length()==0)  path=sa;
    if(sa<path) path=sa;
    entry.close();
  }
  //sa=F("fs_del ");
  //sa+=n;
  if( (n>maxFiles) || ( (fs_usedBytes*2) > fs_totalBytes ) ){
    SPIFFS.remove(path); delay(10);
    //sa+=" "+path;
  }
  //addLog(sa);
}
