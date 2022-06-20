function reqRent(isbn)
{
    const url = "/api/";
    var post = new XMLHttpRequest();
    post.open("POST", url);

    post.onload = () =>
    {
        var res = JSON.parse(post.responseText);
    }

    var data = new FormData();
    data.append("type", "rental");
    data.append("isbn", isbn);

    post.send(data);
}