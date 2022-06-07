<?php 
ini_set('display_errors', 1);
ini_set('display_startup_errors', 1);
error_reporting(E_ERROR);

session_start();

function send_req($req)
{
    try
    {
        $req = json_encode($req);
        $sock = socket_create(AF_INET, SOCK_STREAM, SOL_TCP);
        if(!$sock) return '{"resID":3,"msg":"Unable to create socket"}';
        $conn = socket_connect($sock, "127.0.0.1", 8080);
        if(!$conn) return '{"resID":3,"msg":"Unable to connect to Back-End Server"}';
        socket_write($sock, $reqs, strlen($reqs));
        $res = socket_read($sock, 1024);
    }
    catch(Exception $e)
    {
        return '{"resID":3, "msg":"' . $e->getMessage() . '"}';
    }
    finally
    {
        socket_close($sock);
    }
    if($res) return $res;
    return '{"resID":3, "msg":"Unknown Error occured"}';
}
if($_POST["type"] == "login") //login req
{
    if(!isset($_SESSION["ID"]))
    {
        $req["requestID"] = 1;
        $req["req"]["id"] = $_POST["id"];
        $req["req"]["passwd"] = hash("sha256", $_POST["pw"]);
    
        $res = json_decode(send_req($req));
    
        if($res->resID == 1)
        {
            $_SESSION["ID"] = htmlspecialchars($_POST["id"]);
            echo('{"res":true,"msg":"Login Success"}');
        }
        else if($res->resID == 2) echo('{"res":false, "msg":"Account is not exist"}');
        else echo('{"res":false, "msg":"' . $res->msg . '"}');
    }
    else echo('{"res":false, "msg":"Already Logged in"}');
}
else if($_POST["type"] == "booklist")
{

}
else if($_POST["type"] == "")
{
    
}


?>