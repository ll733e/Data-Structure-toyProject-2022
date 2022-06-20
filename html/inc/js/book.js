function getBook(isbn)
{
    const url = "/api/";
    var post = new XMLHttpRequest();
    post.open("POST", url);

    post.onload = () =>
    {
        var res = JSON.parse(post.responseText);
        if(res.res == 1)
        {
            curform.title.innerHTML = res.book.bookTitle;
            curform.author.innerHTML = res.book.author;
            curform.publisher.innerHTML = res.book.publisher;
            curform.publishYear.innerHTML = res.book.publishYear;
            curform.isAvailable.innerHTML = res.book.isAvailable ? "대여 가능" : "대여 불가";
        }
        else if(res.res == 2)
        {
            alert("해당 도서를 찾을 수 없습니다.");
            document.href="/";
        }
        else
        {
            alert(res.msg);
        }
    }

    var data = new FormData();
    data.append("type", "rental");
    data.append("isbn", isbn);

    post.send(data);
}