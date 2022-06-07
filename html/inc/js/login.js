function do_login()
{
    const url = "/api/";
    var post = new XMLHttpRequest();
    post.open("POST", url);

    post.onload = () =>
    {
        var res = JSON.parse(post.responseText);
        if(res.res)
        {
            location.href = "/"
        }
        else
        {
            alert(res.msg);
        }
    }

    var data = new FormData();
    data.append("type", "login");
    data.append("id", login_form.user_id.value);
    data.append("pw", login_form.user_pw.value);

    post.send(data);

    return false;
}