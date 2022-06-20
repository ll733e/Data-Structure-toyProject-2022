function search_book(page)
{
    const url = "/api/";
    var post = new XMLHttpRequest();
    post.open("POST", url);

    post.onload = () =>
    {
        booklist.innerHTML = "";
        page_dis.innerHTML = "";
        var res = JSON.parse(post.responseText);
        if(res.res == 1)
        {
            for(var row of res.book)
            {
                var available = row.isAvailable ? "onclick='reqRent(" + row.isbn + ")'":" disabled";
                console.log(row);
                booklist.innerHTML += '<tr><td><div class="container"><div class="row"><div class="col-auto me-auto"><a href="?p=book&isbn=' + row.isbn + '">' + row.bookTitle + '</a><p>' + row.author + ' / ' + row.publisher + ' / ' + row.publishYear + '</p></div><div class="col-auto"><br><button type="submit" class="btn btn-primary"' + available + '>대여</button></div></div></td></tr>';
            }
            for(var i = 0; i < res.count/10;i++)
            {
                page_dis.innerHTML += '<li class="page-item"><a class="page-link" onclick="search_book(' + i+1 + ');">' + (i+1)+ '</a></li>';
            }
        }
        else booklist.innerHTML = "<div><p>There is no result!</p></div>";
    }

    var data = new FormData();
    data.append("type", "booklist");
    data.append("debug", "1");
    data.append("searchQuery", search_form.q.value);
    data.append("page", page);

    post.send(data);

    return false;
}

function default_book()
{
    booklist.innerHTML = "<div><p>검색 기능을 사용하세요.</p></div>";
}