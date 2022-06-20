function search_book()
{
    const url = "/api/";
    var post = new XMLHttpRequest();
    post.open("POST", url);

    post.onload = () =>
    {
        booklist.innerHTML = "";
        var res = JSON.parse(post.responseText);
        if(res.res == 1)
        {
            for(var row of res.book)
            {
                var available = row.isAvailable ? "onclick='reqRent(" + row.isbn + ")'":" disabled";
                console.log(row);
                booklist.innerHTML += '<tr><td><div class="container"><div class="row"><div class="col-auto me-auto"><a href="?p=book&isbn=' + row.isbn + '">' + row.bookTitle + '</a><p>' + row.author + ' / ' + row.publisher + ' / ' + row.publishYear + '</p></div><div class="col-auto"><br><button type="submit" class="btn btn-primary"' + available + '>대여</button></div></div></td></tr>';
            }
        }
        else booklist.innerHTML = "<div><p>There is no result!</p></div>";
    }

    var data = new FormData();
    data.append("type", "booklist");
    data.append("debug", "1");
    data.append("searchQuery", search_form.q.value);
    data.append("limit", 20);

    post.send(data);

    return false;
}

function default_book()
{

}