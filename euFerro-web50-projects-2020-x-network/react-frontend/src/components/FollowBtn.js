import { useEffect, useState } from "react";
import "./FollowBtn.css"


function FollowBtn({user, setUser}) {
    const [isFollowing, setFollowing] = useState(undefined);
    
    const logged_user = JSON.parse(localStorage.getItem('logged_user'));

    function applyUnfollowBtnStyle() {
        const flwn_btn = document.querySelector("#following-btn");
        flwn_btn.addEventListener('mouseover', () => {
            const flwn_btn = document.querySelector("#following-btn");
            flwn_btn.innerHTML = 'unfollow';
            flwn_btn.style.color = '#ff0000';
            flwn_btn.style.backgroundcColor = '#330000';
        })
        flwn_btn.addEventListener('mouseout', () => {
            flwn_btn.style = '';
            flwn_btn.innerHTML = 'following';
        })
    }

    function followUser() {
        const csrf_token = document.cookie.split(';')[0].split('=')[1];
        console.log(`csrf_token: ${csrf_token}`);

        const formData = new FormData();
        formData.append('user_id', logged_user.user_id);
        formData.append('follow_id', user.user_id);

        fetch('/follow', {
            "method": "POST",
            "credentials": "same-origin",
            "headers": {
                "X-CSRFToken": csrf_token
            },
            "body" : formData
        })
        .then(response => response.json())
        .then(response => {
            // do something
            if (response.ok) {
                console.log(response.ok);
                const new_logged_user = {
                    ...logged_user,
                    following_username_list: [...logged_user.following_username_list, user.username]
                }
                localStorage.setItem('logged_user', JSON.stringify(new_logged_user));
                setFollowing(true);
                setUser(user);
            }
            if (response.error) {
                alert(response.error)
            }
        })
        return false;
    }

    function unfollowUser() {
        const csrf_token = document.cookie.split(';')[0].split('=')[1];

        fetch(`/unfollow/${user.user_id}`, {
            "method": "DELETE",
            "credentials": "same-origin",
            "headers": {
                "X-CSRFToken": csrf_token
            }
        })
        .then(response => response.json())
        .then(response => {
            if (response.ok) {
                console.log(response.ok);
                const new_following_username_list = logged_user.following_username_list.filter(username => {
                    return username !== user.username;
                })
                const new_logged_user = {
                    ...logged_user,
                    following_username_list: new_following_username_list
                }
                localStorage.setItem('logged_user', JSON.stringify(new_logged_user));
                setFollowing(false);
                setUser(user);
            }
            if (response.error) {
                alert(response.error)
            }
        })
        return false;
    }

    useEffect(() => {
        if (logged_user !== null) {
            var is_following = logged_user.following_username_list.some(username => {
                if (username === user.username) {
                    return true;
                }
                return false;
            });
            if (isFollowing === undefined) {
                setFollowing(is_following);
            }
        }
        if (isFollowing) {
            applyUnfollowBtnStyle();
        }
    }, [isFollowing])

    return(
        <>
        {isFollowing ? (
            <button onClick={unfollowUser} id="following-btn" className="secondary-btn" type="submit">following</button>
        ) : (
            <button onClick={followUser} id="follow-btn" className="primary-btn" type="submit">follow</button>
        )}
        </>

    );

}

export default FollowBtn;