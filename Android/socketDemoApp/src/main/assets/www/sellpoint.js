app.initialize();
//Utils
function removeInitialChar(string){
   var result = ""
   for (var i=1; i < string.length;i++){
      result += string[i];
   }
   return result;
}
//Utils End
var TCPConn = function(){
    this.host = "10.42.0.1";
    this.port = 50009;
    this.parent = null;
}

var SellPoint = function (){
    self.connection_layer = new TCPConn();
    this.host = "10.42.0.1";
    this.port = 50009;
}
var CONN_DEVICE = {
  TCP : 0
 // BLE : 1,
 // BLUETOOTH : 2
}
//Signals
function barCodeScanner(ev){

}

function magneticScanner(ev){

}

var barCodeScannerPacketRead = function(){

}

barCodeScannerPacketRead.connect =  function (callback){
    barCodeScanner = callback;
}

var magneticScannerPacketRead = function(){

}
magneticScannerPacketRead.connect =  function (callback){
    magneticScanner = callback;
}

/*** BarCodeScanner ***/
//Default Pool Key
key = "";


var BarCodeScanner = function(){
//Constructor  
}

var MagneticScanner = function(){
//Constructor  
}

BarCodeScanner.packetRead = barCodeScannerPacketRead;
MagneticScanner.packetRead = magneticScannerPacketRead;

function stub(d) {
    console.log(d);
    //alert("Connected");
}

function req_disconnect(d)
{
    document.getElementById("result").innerHTML = "NOT CONNECTED";

}

function repeat_validation()
{
   window.tlantic.plugins.socket.isConnected(key, stub, req_disconnect);
   window.setTimeout(repeat_validation, 2000);
}

function on_connect(d) {
    document.getElementById("result").innerHTML = "CONNECTED";
}

TCPConn.prototype.onConnect = function (k) {
    console.log('Established connection with ', k);
    document.getElementById("result").innerHTML = "CONNECTED";
    window.tlantic.plugins.socket.isConnected(key, stub, req_disconnect);

    key = k;
}

TCPConn.prototype.connect = function () {
    window.tlantic.plugins.socket.connect(this.onConnect, req_disconnect, this.host, this.port);


}

TCPConn.prototype.send = function (data) {
    //data = data + ""
    window.tlantic.plugins.socket.send(stub, stub, key, data);
}

TCPConn.prototype.disconnect = function () {
    window.tlantic.plugins.socket.disconnect(req_disconnect, req_disconnect, key);
}

TCPConn.prototype.disconnectAll = function () {
    window.tlantic.plugins.socket.disconnectAll(req_disconnect, req_disconnect);
}

TCPConn.prototype.isConnected = function () {
    window.tlantic.plugins.socket.isConnected(key, stub, req_disconnect);

}

/*** SellPoint ***/
SellPoint.prototype.initialize_connection_layer = function (device, host, port) {
   if (device == CONN_DEVICE.TCP){
       this.connection_layer = new TCPConn();
       this.connection_layer.host = host;
       this.connection_layer.port = port;
       this.connection_layer.parent = this;
       document.addEventListener('SOCKET_RECEIVE_DATA_HOOK', this.connCallback);
       window.setTimeout(repeat_validation, 2000);

   }
}

SellPoint.prototype.onConnect = function (k) {
    console.log('Established connection with ', k);
    key = k;
}

SellPoint.prototype.connect = function () {
    this.connection_layer.connect(this.onConnect, stub, this.host, this.port);
}

SellPoint.prototype.send = function (data) {
    this.connection_layer.send(data);
}

SellPoint.prototype.disconnect = function () {
    this.connection_layer.disconnect();
}

SellPoint.prototype.disconnectAll = function () {
    this.connection_layer.disconnectAll();
}

SellPoint.prototype.isConnected = function () {
    this.connection_layer.isConnected();
}

SellPoint.prototype.connCallback = function (ev) {
    //this.connection_layer.connCallback(ev);
  if (ev.metadata.data[0] == 'B')
      barCodeScanner(ev);
  else if (ev.metadata.data[0] == 'M')
      magneticScanner(ev);
}

SellPoint.prototype.barCodeScanner = function (ev) {
  barCodeScanner = ev;
}

/*** SellPoint Instance ***/
var sellPoint = new SellPoint();

/*** ESCPOSPrinter ***/
var ESCPOSPrinter = function (){
}

ESCPOSPrinter.init = function (){
  sellPoint.send("i</end>");
}

ESCPOSPrinter.printRawText = function (text){
  sellPoint.send("0" + text + "</end>");
}

ESCPOSPrinter.cutPaper = function (fullCut){
  sellPoint.send('1' + (fullCut ? '1' :'0') + "</end>");
}

ESCPOSPrinter.sendPulseToCashDrawer = function (pin){
  sellPoint.send('2' + parseInt(pin) + "</end>");
}

ESCPOSPrinter.setTextProperties = function (align, font, type, width, height){
  sellPoint.send('3' + parseInt(align) + ':' + parseInt(font) + ':' + parseInt(type) + ':' + parseInt(width) + ':' + parseInt(height) + "</end>");
}

ESCPOSPrinter.feedControl = function (crl){
  sellPoint.send('4' + parseInt(crl) + "</end>");
}

ESCPOSPrinter.printImage = function (pathImage, rightTab, sizeScale){
  sellPoint.send('5' + parseInt(pathImage.length) + ":" + pathImage + parseInt(rightTab) + ":" + parseInt(sizeScale) + "</end>");
}

ESCPOSPrinter.printBarcode = function (code, type, width, height, pos, font){
  sellPoint.send('6' + parseInt(code.length) + code + parseInt(type) + ":" + parseInt(width) + ":" + parseInt(height) + ":" + parseInt(pos) + ":" + parseInt(font)+ "</end>");
}

ESCPOSPrinter.printQRCode = function (code, errCorrect, moduleSize){
  sellPoint.send('7' + parseInt(code.length) + code + parseInt(errCorrect) + ":" + parseInt(moduleSize)+ "</end>");
}

ESCPOSPrinter.setTimeout = function (value){
  sellPoint.send('8' + parseInt(value)+ "</end>");
}

sellPoint.initialize_connection_layer(CONN_DEVICE.TCP, "10.42.0.23", 8888);
//Bellow code is deprecated, is just for study

function onConnect(k) {
    console.log('Established connection with ', k);
    key = k;
}

function connect() {
    window.tlantic.plugins.socket.connect(onConnect, stub, host, 50009);

}

function send() {
    window.tlantic.plugins.socket.send(stub, stub, key, data);
}

function disconnect() {
    window.tlantic.plugins.socket.disconnect(stub, stub, key);
}

function disconnectAll() {
    window.tlantic.plugins.socket.disconnectAll(stub, stub);
}

function isConnected() {
    window.tlantic.plugins.socket.isConnected(key, stub, stub);
}
