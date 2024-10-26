

document.addEventListener('DOMContentLoaded', () => {

    document.querySelector("#following-btn").onmouseover = show_unfollow;
    document.querySelector("#following-btn").onmouseout = hide_unfollow;

    document.querySelector("#follow-form").onsubmit = follow;
    document.querySelector("#unfollow-form").onsubmit = unfollow;

    // Cookie stuff (no utility here)
    const csrftoken = getCookie('csrftoken');
    // console.log(csrftoken);
    // console.log(document.cookie);
})


function show_unfollow() {
    btn = document.querySelector("#following-btn");
    btn.innerHTML = "unfollow";
    btn.style.backgroundColor = "#330000";
    btn.style.border = "1px solid #cc0000";
    btn.style.color = "#cc2222";
}
function hide_unfollow() {
    btn = document.querySelector("#following-btn");
    btn.innerHTML = "following";
    btn.style.backgroundColor = "black"
    btn.style.border = "1px solid white";
    btn.style.color = "white";
}

function follow() {
    csrf_token = document.querySelector('[name=csrfmiddlewaretoken]').value;
    user_id = document.querySelector("#user-id").value;
    follow_id = document.querySelector("#follow-id").value;

    fetch("/follow", {
        "method": "POST",
        "credentials": "same-origin",
        "headers": {
            "X-CSRFToken": csrf_token
        },
        "body": JSON.stringify({
            "user_id": user_id,
            "follow_id": follow_id
        })
    })
    .then(response => response.json())
    .then(response => {
        if (response.error) {
            alert(response.error)
        }
        if (response.ok) {
            document.querySelector("#follow-form").style.display = "none";
            document.querySelector("#unfollow-form").style.display = "block";
            console.log(response.ok);
        }
    })

    // Prevent default
    return false;
}

function unfollow() {
    // Get inputs
    csrf_token = document.querySelector('[name=csrfmiddlewaretoken]').value;
    user_id = document.querySelector("#user-id").value;
    follow_id = document.querySelector("#follow-id").value;

    fetch("/follow", {
        "method": "DELETE",
        "credentials": "same-origin",
        "headers": {
            "X-CSRFToken": csrf_token
        },
        "body": JSON.stringify({
            "user_id": user_id,
            "follow_id": follow_id
        })
    })
    .then(response => response.json())
    .then(response => {
        if (response.error) {
            alert(response.error)
        }
        if (response.ok) {
            document.querySelector("#follow-form").style.display = "block";
            document.querySelector("#unfollow-form").style.display = "none";
            console.log(response.ok);
        }
    })

    return false;
}


function getCookie(name) {
    let cookieValue = null;
    if (document.cookie && document.cookie !== '') {
        const cookies = document.cookie.split(';');
        for (let i = 0; i < cookies.length; i++) {
            const cookie = cookies[i].trim();
            // Does this cookie string begin with the name we want?
            if (cookie.substring(0, name.length + 1) === (name + '=')) {
                cookieValue = decodeURIComponent(cookie.substring(name.length + 1));
                break;
            }
        }
    }
    return cookieValue;
}


