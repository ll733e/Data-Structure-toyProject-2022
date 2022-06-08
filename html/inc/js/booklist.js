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
            for(var row of res.result)
            {
                console.log(row);
                booklist.innerHTML += '<tr><td><div class="container"><a href="?p=book&isbn=' + row.isbn + '">' + row.bookTitle + '</a><p>' + row.author + ' / ' + row.publisher + ' / ' + row.year + '</p></div></td></tr>';
            }
        }
        else booklist.innerHTML = "<div><p>There is no result!</p></div>";
    }

    var searchType = "";
    if(search_form.title.checked) searchType = "title";
    else if(search_form.author.checked) searchType = "author";
    else if(search_form.isbn.checked) searchType = "isbn";
    else if(search_form.year.checked) searchType = "year";
    else searchType = "default";

    var data = new FormData();
    data.append("type", "booklist");
    data.append("searchQuery", search_form.q.value);
    data.append("searchType", searchType);
    data.append("limit", 20);

    post.send(data);

    return false;
}

function default_book()
{

}