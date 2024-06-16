#include "html.h"

String setJsonData::data(const String& waterLevel, const String& msg, const String& timeStamp, const String& nameOfEsp, const String& fwVersion) {
    return "{ \"waterLevel\": \"" + waterLevel + "\", \"msg\": \"" + msg + "\", \"timeStamp\": \"" + timeStamp + "\", \"name_device\": \"" + nameOfEsp + "\", \"fwVersion\": \"" + fwVersion + "\"}";
}

String setJsonData::page = R"(
    <html>
    <body>
      <h1>Water level</h1>
      <p>Name of device: <span id="nameOfEsp">Cargando nombre...</span></p>
      <p>El nivel de agua es: <span id="waterLevel">Cargando nivel de agua...</span> cm</p>
      <h2>Mensaje</h2>
      <p><span id="msg">Cargando mensaje...</span></p>
      <p>timeStamp: <span id="timeStamp">Cargando hora...</span></p>
      <br>
      <hr>
      <p>firmware Version: <span id="fwVersion">Cargando versión...</span></p>
      <script>
        function getData() {
          fetch('/data')
            .then(response => response.json())
            .then(data => {
                document.getElementById('waterLevel').textContent = data.waterLevel;
                document.getElementById('msg').textContent = data.msg;
                document.getElementById('timeStamp').textContent = data.timeStamp;
                document.getElementById('nameOfEsp').textContent = data.name_device;
                document.getElementById('fwVersion').textContent = data.fwVersion;
            });
        }
        // Solicita los datos cada 5 segundos
        setInterval(getData, 5000);
        // Solicita los datos inmediatamente al cargar la página
        getData();
      </script>
    </body>
    </html>
  )";