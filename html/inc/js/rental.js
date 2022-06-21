function reqRent(obj, isbn)
{
    console.log(isbn);
    const url = "/api/";
    var post = new XMLHttpRequest();
    post.open("POST", url);

    post.onload = () =>
    {
        var res = JSON.parse(post.responseText);
        if(res.res == 1)
        {
            obj.className = "btn btn-danger";
            obj.innerHTML = "반납";
            obj.onclick = reqReturn(obj, isbn);
            alert(res.msg);
        }
        else if(res.res == 2)
        {
            obj.disabled = true;
            alert(res.msg);
        }
    }

    var data = new FormData();
    data.append("type", "rental");
    data.append("isbn", isbn);

    post.send(data);
}

function reqReturn(obj, isbn)
{
    const url = "/api/";
    var post = new XMLHttpRequest();
    post.open("POST", url);

    post.onload = () =>
    {
        var res = JSON.parse(post.responseText);
        if(res.res == 1)
        {
            obj.className = "btn btn-dark";
            obj.innerHTML = "대여";
            obj.onclick = reqRent(obj, isbn);
            alert(res.msg);
        }
        else if(res.res == 2)
        {
            obj.disabled = true;
            alert(res.msg);
        }
    }

    var data = new FormData();
    data.append("type", "return");
    data.append("isbn", isbn);

    post.send(data);
}