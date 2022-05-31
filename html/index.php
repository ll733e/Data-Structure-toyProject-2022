<HTML>
<?php include_once("./inc/head.php"); ?>
    <body>
		<div class="container">
			<br>
			<br>
			<br>
			<br>
<?php
include_once("./inc/header.php");
if($_GET["p"] == "login")
{
?>
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
<?php
}
else if($_GET["p"] == "logout")
{
	session_destroy();
?>
	<script>location.href = "/";</script>
<?php
}
else if($_GET["p"] == "search")
{
?>
<script src="inc/js/booklist.js"></script>
<div class="row">
	<div class="col-md-10">
		<form onsubmit="return search_book()" onload="default_book()" id="search_form">
			<div class="row">
				<div class="col">
					<input type="text" class="form-control" id="q" placeholder="Search">
				</div>
				<div class="col">
					<div class="form-check form-check-inline">
						<input class="form-check-input" type="radio" id="title" name="qtype" checked>
						<label class="form-check-label" for="title">Title</label>
					</div>
					<div class="form-check form-check-inline">
						<input class="form-check-input" type="radio" id="author" name="qtype">
						<label class="form-check-label" for="author">Author</label>
					</div>
					<div class="form-check form-check-inline">
						<input class="form-check-input" type="radio" id="isbn" name="qtype">
						<label class="form-check-label" for="isbn">ISBN10</label>
					</div>
					<div class="form-check form-check-inline">
						<input class="form-check-input" type="radio" id="year" name="qtype">
						<label class="form-check-label" for="year">Year</label>
					</div>
				</div>
				<div class="col">
					<button class="btn btn-primary" type="submit">찾기</button>
				</div>
			</div>
		</form>
	</div>
</div>
<table class="table">
	<thead>
		<tr>
			<th scope="col"></th>
		</tr>
	</thead>
	<tbody id="booklist">
		<tr>
			<td>
				<div>

				</div>
			</td>
		</tr>
<!-- Adasd -->
	</tbody>
</table>
<?php
}
else
{

}
?>
			<br>
			<br>
			<br>
		</div>
    </body>
</HTML>