import "./Profilepage.css";
import { useState, useEffect } from "react";
import { Link, useLocation, useParams } from "react-router-dom";
import Post from "../components/Post";
import FollowBtn from "../components/FollowBtn";
import BackBar from "../components/BackBar";


function Profilepage() {

    const location = useLocation();
    const [posts, setPosts] = useState([]);
    const [is_loading, setLoading] = useState(false);
    const [user, setUser] = useState(undefined);
    const {username} = useParams();
    const [error, setError] = useState('You are is offline :( connect to the internet!');

    const logged_user = JSON.parse(localStorage.getItem('logged_user'));

    if (logged_user !== null) {
        console.log(logged_user);
    }

    function getUser() {
        setLoading(true);
        console.log('username: ' + username)

        fetch(`/profile?username=${username}`)
        .then(response => response.json())
        .then(response => {
            if (response.error) {
                setError(response.error);
            }
            if (response.user) {
                setUser(JSON.parse(response.user));
            }
            setLoading(false);
        });
    }

    function getUserPosts() {
        setLoading(true);
        fetch(`/posts?q=user-posts&username=${user.username}`, {
            "method": "GET",
        })
        .then(response => response.json())
        .then(response => {
            if (response.error) {
                alert(`(!) Error - ${response.error}`);
                return false;
            } else {
                const user_posts = JSON.parse(response);
                // console.log(user_posts);
                setPosts(posts.concat(user_posts));
            }
            setLoading(false);
        })
    }

    useEffect(() => {
        console.log('Page Updated');
        if (user === undefined) {
            // If no profile user was set
            getUser();
        }
        if (user !== undefined) {
            console.log(user);
            if (user.username !== username) {
                // User changed
                getUser();
                setPosts([]);
            }
            if (posts.length === 0) {
                // Get new user's posts
                getUserPosts();
            }
        }

    }, [user, location, error])

    if (user) {
        return(
            <>
                <BackBar title={username}/>
                
                <div className="post-div">
    
                    <div className="profile-header">
    
                        <div className="profile-img-div">
                            <img
                                className="profile-img"
                                src={user.profile_picture_url}
                                alt="Profile Avatar"
                            />
                        </div>
    
                        <div className="profile-header-item">
    
                            <div className="profile-name">
                                {user.first_name} {user.last_name}
                            </div>
    
                            <div className="follow-div">

                                {logged_user !== null ? (
                                    <>
                                    {logged_user.username === username ? (
                                        <><button id="edit-profile-btn" className="secondary-btn" type="submit">edit profile</button></>
                                    ) : (
                                        <><FollowBtn user={user} setUser={setUser}/></>
                                    )}
                                    </>
                                ) : (
                                    <>
                                    <Link to={'/login'}>
                                    <button id="follow-btn" className="primary-btn" type="submit">follow</button>
                                    </Link>
                                    </>
                                )}
    
                            </div>
                        </div>
    
                        <div className="subtle-text">
                            @{user.username}
                        </div>
    
                        <div className="profile-header-item">
                            <div className="profile-header-item">
                                {user.followers_count} <span className="subtle-text mx-1">Followers</span>
                            </div>
                            <div className="profile-header-item">
                                {user.following_count} <span className="subtle-text mx-1">Following</span>
                            </div>
                        </div>
    
                    </div>
                    
                    <div id="all-posts-div">
    
                        {is_loading ? (
                            <div className='loading-container'>
                                <div className="lds-ring"><div></div><div></div><div></div><div></div></div>
                            </div>
                        ) : (
                            <></>
                        )}
    
                        {posts.map(post => {
                            return <Post
                                key={post.key}
                                post={post}
                            />;
                        })}
    
                        {posts.length === 0 ? (
                            <div className="nothing-here">nothing here yet.</div>
                        ) : (
                            <></>
                        )}
                    
                    </div>
    
                </div>
            </>
            );
    } else {
        return (<div className="nothing-here">{error}</div>);
    }

    }



export default Profilepage;