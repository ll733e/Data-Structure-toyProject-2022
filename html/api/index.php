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
        if(!$sock) return '{"res":-1,"msg":"Unable to create socket"}';
        $conn = socket_connect($sock, "127.0.0.1", 8080);
        if(!$conn) return '{"res":-1,"msg":"Unable to connect to Back-End Server"}';
        socket_write($sock, $reqs, strlen($reqs));
        $res = socket_read($sock, 2048);
    }
    catch(Exception $e)
    {
        return '{"res":-1, "msg":"' . $e->getMessage() . '"}';
    }
    finally
    {
        socket_close($sock);
    }
    if($res) return $res;
    return '{"res":-1, "msg":"Unknown Error occured"}';
}
if($_POST["type"] == "login")
{
    if(!isset($_SESSION["ID"]))
    {
        $req["reqType"] = 1;
        $req["req"]["id"] = $_POST["id"];
        $req["req"]["passwd"] = hash("sha256", $_POST["pw"]);
    
        $res = json_decode(send_req($req));
    
        if($res->res == 1)
        {
            $_SESSION["ID"] = htmlspecialchars($_POST["id"]);
            echo('{"res":1,"msg":"Login Success"}');
        }
        else if($res->res == 2) echo('{"res":-1, "msg":"Account is not exist"}');
        else echo('{"res":-1, "msg":"' . $res->msg . '"}');
    }
    else echo('{"res":-1, "msg":"Already Logged in"}');
}
else if($_POST["type"] == "bookinfo")
{
    $req["reqType"] = 3;
    $req["req"]["isbn"] = $_POST["isbn"];
    $req["req"]["id"] = isset($_SESSION["ID"]) ? $_SESSION["ID"] : "";

    $res = send_req($req);

    echo $res;
}
else if($_POST["type"] == "booklist")
{
    if($_POST["debug"] == "1")
    {
        $res["res"] = 1;
        $res["msg"] = "";
        $res["count"] = 1;
        $res["book"][0]["isbn"] = "1234";
        $res["book"][0]["bookTitle"] = "조별 과제를 잘 하는 법";
        $res["book"][0]["publisher"] = "고려대학교";
        $res["book"][0]["author"] = "이서준";
        $res["book"][0]["publishYear"] = 2022;
        $res["book"][0]["isAvailable"] = true;

        echo(json_encode($res));
    }
    else
    {
        $req["reqType"] = 5;
        $req["req"]["query"] = $_POST["searchQuery"];
        $req["req"]["id"] = isset($_SESSION["ID"]) ? $_SESSION["ID"] : "";
        $req["req"]["page"] = (is_numeric($_POST["page"]) && intval($_POST["limit"]) > 0 ) ? intval($_POST["limit"]) : 1;

        $res = send_req($req);

        echo $res;
    }
}
else if($_POST["type"] == "rental")
{
    if(isset($_SESSION["ID"]))
    {
        $req["reqType"] = 7;
        $req["req"]["isbn"] = $_POST["isbn"];
        $req["req"]["ID"] = $_SESSION["ID"];

        $res = send_req($req);

        echo $res;
    }
    else echo('{"res":-1, "msg":"User not logged in"}');
}
else if($_POST["type"] == "return")
{
    if(isset($_SESSION["ID"]))
    {
        $req["reqType"] = 9;
        $req["req"]["isbn"] = $_POST["isbn"];
        $req["req"]["ID"] = $_SESSION["ID"];

        $res = send_req($req);

        echo $res;
    }
    else echo('{"res":-1, "msg":"User not logged in"}');
}
else
{
    echo("404");
}
?>