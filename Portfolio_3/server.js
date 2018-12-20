var http = require('http');

var fs = require('fs');



function handle_incoming_request (req, res) {

    console.log("INCOMING REQUEST: " + req.method + " " + req.url);

    load_sensor_data(function(err, readings){

    if (err) { 

       console.log("Couldn't read file");

    }

    console.log(readings);

//var data = [console.log(readings)];
   res.writeHead(200, { "Content-Type": "application/json"});

var data= readings.split(',');	
for(var i=0; i< (readings);i++)
{
res.write(JSON.stringify({Temperature:data[0],Humidity:data[1],WindSpeed:data[2],Time:data[3],Location:data[4]},null,'\t'));
   res.end();
 }              
   });

}

function load_sensor_data(callback) {

   fs.readFile(

   "sensorlog.txt",'utf8',

   function (err, readings) {

   if (err) {

   callback(err);

return;



}

callback(null, readings);

}

);

}

var s = http.createServer(handle_incoming_request);


s.listen(8080);