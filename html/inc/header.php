<?php 
session_start();
?>
<header>
    <nav class="navbar navbar-expand-md navbar-dark fixed-top bg-dark">
        <div class="container-fluid">
            <a class="navbar-brand" href="">Lib</a>
            <button class="navbar-toggler" type="button" data-bs-toggle="collapse" data-bs-target="#navbarCollapse" aria-controls="navbarCollapse" aria-expanded="false" aria-label="Toggle navigation">
                <span class="navbar-toggler-icon"></span>
            </button>
            <div class="collapse navbar-collapse" id="navbarCollapse">
                <ul class="navbar-nav me-auto mb-2 mb-md-0">
                    <li class="nav-item">
                        <a class="nav-link active" href="?p=search">검색</a>
                    </li>
                    <?php if(isset($_SESSION["ID"])) { ?>
                    <li class="nav-item">
                        <a class="nav-link" href="?p=rentlist">대여 목록</a>
                    </li>
                    <?php } ?>
                </ul>
                <ul class="navbar-nav d-flex">
                    <?php if(isset($_SESSION["ID"])) { ?>
                    <li class="nav-item dropdown">
                        <a class="nav-link dropdown-toggle" href="#" id="navbarDropdown" role="button" data-bs-toggle="dropdown" aria-expanded="false"><?php echo $_SESSION["ID"]; ?></a>
                        <ul class="dropdown-menu" aria-labelledby="navbarDropdown">
                            <li><a class="dropdown-item" href="?p=logout">로그아웃</a></li>
                        </ul>
                    </li>
                    <?php } else { ?>
                    <li class="nav-item">    
                        <a class="nav-link active" href="?p=login">로그인</a>
                    </li>
                    <?php } ?>
                </ul>
            </div>
        </div>
    </nav>
</header>