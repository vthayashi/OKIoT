void addLog(String text){
  log_buffer+=text+"|";
  if(log_buffer.length()>500) log_buffer=log_buffer.substring(log_buffer.indexOf("|")+1);
}

void log_loop100(){
  if(year()<2019) return;
  if( (loop100count%10==0)&&(log_buffer.indexOf("|")>0) ){
    time_t t=now();
    if(year(t)>2018){
      String sa;
      sa=log_buffer.substring(0,log_buffer.indexOf("|"));
      log_buffer=log_buffer.substring(log_buffer.indexOf("|")+1);
      //
      log_recent+=String(t)+" "+sa+"|";
      if(log_recent.length()>200){ log_recent=log_recent.substring(log_recent.indexOf("|")+1); }
      //
      fs_gravar_log(t, sa);
    }
  }
}

void fs_gravar_log(uint32_t t, String text){
  String path,sb; path=F("/log/");
  sb=year(t); sb=sb.substring(2); path+=sb;
  if(month(t)<10) sb="0"; else sb="";
  sb+=month(t); path+=sb;
  if(day(t)<10) sb="0"; else sb="";
  sb+=day(t); path+=sb; path+=F(".txt");
  File rFile = SPIFFS.open(path,"a");
  if(!rFile){
    Serial.println(F("Erro ao abrir arquivo!"));
  }else{
    sb=t; sb+=" "; sb+=text;
    rFile.println(sb);
  }
  rFile.close(); delay(10);
}

void handleView(){
  String sa, pg;
  sa=F("/view.htm"); if(handleFileRead(sa)) return;
  pg=F(
    "<html><head>\n"
    "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n"
    
    "<style>\n"
    "  html,input,p{font-family:Verdana,Arial,Helvetica,sans-serif;}\n"
    "</style>\n"
    
    "<script>\n"
    " var client=new XMLHttpRequest();\n"
    " client.onreadystatechange=function(){\n"
    "  if(this.readyState==4){\n"
    "   if(this.status==200){\n"
    "    myObj=JSON.parse(this.responseText);\n"
    "   }\n"
    "  }\n"
    " }\n"
    
    " var client2=new XMLHttpRequest();\n"
    " client2.onreadystatechange=function(){\n"
    "  if((this.readyState==4)&&(this.status==200)){ arq=this.responseText; filtrar(); }\n"
    " }\n"
    
    " function filtrar(){\n"
    "  xx='';\n"
    "  sa=arq; sb=''; pg='';\n"
    "  while(sa.indexOf('\\r')>=0){\n"
    "   sb=sa.substring(0,sa.indexOf('\\r'));\n"
    "   sa=sa.substring(sa.indexOf('\\r')+1);\n"
    "   time=sb.substring(0,sb.indexOf(' '));\n"
    "   dados=sb.substring(sb.indexOf(' ')+1);\n"
    "   if(dados.indexOf('Ver: ')==0) dados='<b>'+dados+'</b>';\n"
    "   time++;time--; time*=1000;\n"
    "   var d=new Date(time);\n"
    "   if((dados.indexOf(xx)==0)||(xx=='')){\n"
    //"    sd=d.toLocaleString(); sd=sd.substring(sd.indexOf(' ')+1); pg+=sd+' ';\n"
    "    se=d.toISOString(); se=se.substring(se.indexOf('T')+1); se=se.substring(0,se.indexOf('.')); pg+=se+' ';\n"
    "    if(dados=='Iniciando')pg+='<b>';\n"
    "    pg+=dados+'</b><br>';\n"
    "   }\n"
    "  }\n"
    "  div01.innerHTML=pg;\n"
    " }\n"
    
    " function iniciar(){\n"
    "  sa=location.href; sa=sa.substring(sa.indexOf('url=')+4);\n"
    "  client2.open('GET', '/'+sa, true); client2.send();\n"
    " }\n"
    
    "</script>\n"
    
    "</head>\n"
    "<body onload='iniciar();' topmargin='30'>\n"
    "<h2 align=center>"); pg+=DeviceID; pg+=F("</h2>\n"
    
    "<div style='width:100%' align='center'>\n"

    " <table style='width:100%;max-width:360px;'><tr><td width=100% align=center>\n"
    "  <table border=0><tr><td><pre id='div01' style='text-align:left;font-size:12px;'></pre></td></tr></table>\n"
    "  <span id=span_Versao style='font-size:12px;'>&nbsp;</span>"
    " </td></tr></table>\n"

    "</div>\n"
    "</body>\n"
    "</html>\n"
  );
  server.send(200, "text/html", pg);
}

/////////////////////////////////

void handleLog(){
  String sa, pg;
  sa=F("/log.htm"); if(handleFileRead(sa)) return;
  pg+=F(
    "<html>\n"
    "<head>\n"
    "<meta name='viewport' content='width=device-width, initial-scale=1'>\n"
    "<title></title>\n"
    "<style type='text/css'>\n"
    " html,input,p,button{font:16px Verdana,Arial,Helvetica,sans-serif}\n"
    " p{text-align:left;margin:6px}\n"
    "</style>\n"
    "<script type='text/javascript'>\n"
    "lastFilename='';\n"
    "var sto;\n"
    "var client=new XMLHttpRequest();\n"
    "client.onreadystatechange = function(){\n"
    " if(this.readyState==4){\n"
    "  if(this.status==200){\n"
    "   myFunction(JSON.parse(this.responseText));\n"
    "  }\n"
    " }\n"
    "}\n"
    
    "function myFunction(myObj){\n"
    " if(typeof myObj.list!='undefined'){\n"
    "  list=myObj.list;\n"
    "  list.sort();\n"
    "  sa='';\n"
    "  var j=0;\n"
    "  for(i in list){\n"
    "   sb=list[i];\n"
    "   size=sb.substring(sb.indexOf(' ')+1); size/=1000;\n"
    "   sb=sb.substring(0,sb.indexOf(' '));\n"
    "   if(sb.substring(0,3)=='log'){\n"
    "    sc=sb.substring(4);\n"
    "    sd='<tr><td>';\n"
    "    j=i; j++;\n"
    "    sd+='<a href='+sb+'>'+sc+'</a></td><td><a href=\"/view?url='+sb+'\">view</a></td><td>'+size.toFixed(0)+'KB</td></tr>';\n"
    "    sa=sd+sa;\n"
    "   }\n"
    "  }\n"
    "  div02.innerHTML=sa;\n"
    " }\n"
    
    "}\n"

    "function iniciar(){\n"
    " client.open('GET', '/?list=/log/', true); client.send();\n"
    
    "}\n"

    "</script>\n"
    "</head>\n"
    
    "<body onload='iniciar()'topmargin=30>\n"
    "<h2 align=center>"); pg+=DeviceID; pg+=F("</h2>\n"
    
    "<div style='width:100%' align='center'>\n"
    
    " <table border=0><tr><td>\n"
    "  <table cellspacing=4 id=div02 style='text-align:left;'></table>\n"
    " </td></tr></table>\n"

    "</div>\n"
    "</body>\n"
    "</html>\n"
  );
  server.send(200, "text/html", pg);
}
