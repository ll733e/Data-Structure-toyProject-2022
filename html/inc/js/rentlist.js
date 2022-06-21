function rentedbooks()
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
                var available = '';
                switch(row.isAvailable)
                {
                    case -1: available = '<button type="submit" class="btn btn-dark" disabled>대여</button>'; break;
                    case 1 : available = '<button type="submit" class="btn btn-dark" onclick="reqRent(' + row.isbn + ');">대여</button>'; break;
                    case 2 : available = '<button type="submit" class="btn btn-danger" onClick="reqReturn(' + row.isbn + ');">반납</button>'; break;
                }
                console.log(row);
                booklist.innerHTML += '<tr><td><div class="container"><div class="row"><div class="col-auto me-auto"><a href="?p=book&isbn=' + row.isbn + '">' + row.bookTitle + '</a><p>' + row.author + ' / ' + row.publisher + ' / ' + row.publishYear + '</p></div><div class="col-auto"><br>' + available + '</div></div></td></tr>';
            }
        }
        else booklist.innerHTML = "<div><p>There is no result!</p></div>";
    }

    var data = new FormData();
    data.append("type", "rentlist");
    post.send(data);

    return false;
}