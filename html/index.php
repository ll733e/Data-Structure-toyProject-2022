<HTML>
<?php include_once("./inc/head.php"); ?>
    <body>
		<?php include_once("./inc/header.php"); ?>
		<div class="container">
			<br>
			<br>
			<br>
<?php
if($_GET["p"] == "login")
{
	if(isset($_SESSION["ID"]))
	{
		echo("Already Logged In!");
		echo('<script>location.href="/";</script>');
	}
	else
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
}
else if($_GET["p"] == "logout")
{
	session_destroy();
	echo('<script>location.href = "/";</script>');
}
else if($_GET["p"] == "search")
{
?>
<script src="inc/js/booklist.js"></script>
<script src="inc/js/rental.js"></script>
<div class="row">
	<div class="col-md-10">
		<form onsubmit="return search_book(1)" id="search_form">
			<div class="row">
				<div class="col">
					<input type="text" class="form-control" id="q" placeholder="Search">
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
				<div><p>검색 기능을 사용하세요.</p></div>
				</div>
			</td>
		</tr>
	</tbody>
</table>
<div class="container">
	<nav>
		<ul class="pagination justify-content-center" id="page_dis">
		</ul>
	</nav>
</div>
<?php
}
else if($_GET["p"] == "book" && isset($_GET["isbn"]))
{
?>
<script onload="getBook('<?php echo(htmlspecialchars($_GET['isbn'])); ?>');" src="inc/js/book.js"></script>
<form id="curform">
	<div class="container-fluid">
		<div class="row">
			<div class="col-md-10">
				<h3 id="title">asd</h3>
			</div>
			<div class="col-md-2">
				<?php if(isset($_SESSION["ID"])) echo('<button type="button" id="btnrent" class="btn btn-dark">대여</button>'); ?>
			</div>
		</div>
		<hr>
		<div class="row">
			<div class="col-md-4">
				<img src="https://sejong.korea.ac.kr/mbshome/mbs/kr/images/sub/s_img0105_0301_1.jpg"/>
			</div>
			<div class="col-md-8">
				<dl>
					<dt>저자</dt>
					<dd id="author"></dd>
					<dt>출판사</dt>
					<dd id="publisher"></dd>
					<dt>출판년도</dt>
					<dd id="publishYear"></dd>
					<dt>대여 가능</dt>
					<dd id="isAvailable"></dd>
				</dl>
			</div>
		</div>
	</div>
</form>
<?php
}
else if($_GET["p"] == "rentlist")
{
?>
<script src="inc/js/rentlist.js"></script>
<script src="inc/js/rental.js" onload="rentedbooks();"></script>
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
				<div><p>대여한 도서가 없습니다!</p></div>
				</div>
			</td>
		</tr>
	</tbody>
</table>
<?php
}
else
{
	echo('<script>location.href = "/?p=login";</script>');
}
?>
			<br>
			<br>
			<br>
		</div>
    </body>
</HTML>