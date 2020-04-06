
void ws_setup(){
  httpUpdater.setup(&server);
  server.on("/", handleRoot);
  String sa;
  sa=F("/view"); server.on(sa.c_str(), handleView);
  sa=F("/log"); server.on(sa.c_str(), handleLog);
  server.begin();
}

void handleRoot(){
  String sa, pg;
  sa=F("time"); if(server.hasArg(sa)){
    wsTimeSet(server.arg(sa));
    time_t t=now(); pg=F("{\"time\":");pg+=t;pg+=F("}");
    server.send(200, "text/json", pg); return;
  }
  sa="list"; if(server.hasArg(sa)){
    String path = server.arg(sa);
    Dir dir = SPIFFS.openDir(path);
    pg = F("{\"list\":[");
    while(dir.next()){
      File entry = dir.openFile("r");
      pg+="\""; pg+=String(entry.name()).substring(1);
      size_t fileSize = dir.fileSize();
      pg+=" "; pg+=String(fileSize); pg+="\",";
      entry.close();
    }
    if(pg.substring(pg.length()-1)==",") pg = pg.substring(0,pg.length()-1);
    pg += "]}";
    server.send(200, "text/json", pg);
    return;
  }
  sa=F("fields");
  if(server.hasArg(sa)){
    String fields;
    fields = server.arg(sa);
    fields=","+fields+",";
    pg="{";
    if(fields.indexOf(F(",time,"))>=0){time_t t=now(); pg+=F("\"time\":");pg+=t;pg+=F(",");}
    if(fields.indexOf(F(",recent,"))>=0){ pg+=F("\"recent\":\""); pg+=log_recent; pg+=F("\","); }
    if(pg.substring(pg.length()-1)==",") pg = pg.substring(0,pg.length()-1);
    pg+="}";
    server.send(200, "text/json", pg);
    return;
  }
  pg+=F(
    "<html>\n"
    "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n"
    "<head>\n"
    
    "<style>\n"
    "  html,input,p{font-family:Verdana,Arial,Helvetica,sans-serif;}\n"
    "</style>\n"
    
    "<script>\n"
    " var client=new XMLHttpRequest();\n"
    " var sto;\n"
    
    " client.onreadystatechange=function(){\n"
    "  if(this.readyState==4 && this.status==200){\n"
    "   myObj=JSON.parse(this.responseText);\n"
    "   if(typeof myObj.time!='undefined'){\n"
    "    time=myObj.time; time*=1000;\n"
    "    var d=new Date(time); se=d.toISOString(); sf=se.substring(0,se.indexOf('T'));\n"
    "    se=se.substring(se.indexOf('T')+1); se=se.substring(0,se.indexOf('.'));\n"
    "    datahora.innerHTML=sf+' '+se;\n"
    "   }\n"
    "   if(typeof myObj.recent!='undefined'){\n"
    "    sa=myObj.recent;\n"
    "    while(sa.indexOf('|')>=0){\n"
    "     sb=sa.substring(0,sa.indexOf('|')); sa=sa.substring(sa.indexOf('|')+1);\n"
    "     time=sb.substring(0,sb.indexOf(' ')); dados=sb.substring(sb.indexOf(' ')+1);\n"
    "     time++;time--; time*=1000; var d=new Date(time);\n"
    "     sd=d.toISOString(); sd=sd.substring(sd.indexOf('T')+1); sd=sd.substring(0,sd.indexOf('.'));\n"
    "     sc=sd+' '+dados;\n"
    "     if(div_rec.innerHTML.indexOf(sc)<0){ div_rec.innerHTML+=sc+'\\n'; }\n"
    "    }\n"
    "   }\n"
    "  }\n"
    " }\n"
    
    "  function iniciar(){ setInterval(loadJson,1000); }"
    "  function loadJson(){ "
    "   client.open('GET', '/?fields=time,recent', true);\n"
    "   client.timeout=900; client.send();\n"
    "  }"
    " function send_time(){\n"
    "  d=new Date(); client.abort();\n"
    "  client.open('GET', '?time='+d.getTime(), true); client.send();\n"
    " }\n"
    "</script>\n"
    "</head>\n"
    
    "<body onload='iniciar();' topmargin=30>\n"
    "<h2 align=center>"); pg+=DeviceID; pg+=F("</h2>\n"
    "<p align=center><b><span id='datahora'>1970-01-01 00:00:00</span></b></p>\n"
    "<p align=center><input type=button value='Enviar Data e Hora' onclick='send_time();' style='border-radius:4px;padding:6px;'></p>"
    "<p align=center><a href='log'>Arquivos</a></p>"

    " <table border=0 align=center><tr><td>\n"
    "  <pre id='div_rec' style='text-align:left;font-size:12px;min-height:20px;'></pre>\n"
    " </td></tr></table>\n"
    
    "<p align=center>Versao: "); pg+=Versao; pg+=F("</p>\n"
    "</body>\n"
    
    "</html>\n"
  );
  server.send(200, "text/html", pg);
}
