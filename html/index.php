<HTML>
<?php include_once("./inc/head.php"); ?>
    <body>
		<div class="container">
<?php
include_once("./inc/header.php");
if($_GET["p"] == "login")
{
?>
<br>
<br>
<br>
<br>
<script src="inc/js/login.js"></script>
	<div class="col-md-5">
		<form id="login_form" class="form-signin" onsubmit="return do_login()">
			<h2 class="form-signin-heading">로그인</h2>
			<input type="text" id="user_id" name="id" class="form-control" placeholder="아이디" required autofocus>
			<input type="password" id="user_pw" name="passwd" class="form-control" placeholder="비밀번호" required>
			<br>
			<button class="btn btn-lg btn-primary btn-block" type="submit">로그인</button>
		</form>
	</div>
	<br>
	<br>
	<br>
<?php
}
else if($_GET["p"] == "logout")
{
	session_destroy();
?>
	<script>location.href = "/";
<?php
}
else
{

}
?>
		</div>
    </body>
</HTML>