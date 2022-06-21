<?php 
$addr = "127.0.0.1";
$port = 8080;

try{
    $socket = socket_create(AF_INET, SOCK_STREAM, SOL_TCP);
    if(!$socket) echo("fuck");
    $con = socket_connect($socket, $addr, $port);
    if(!$con) echo("fuck");

    $w = "Fuckign";
    socket_write($con, $w, strlen($w));
    socket_close();
}
catch(Exception $e)
{

}

?>