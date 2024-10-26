import { useState, useEffect } from 'react'
import "./HeaderNav.css"

function HeaderNav({all_posts_id, following_posts_id, user}) {

    const [state, setState] = useState({
        name: "Homepage",
        on_all_posts: true,
        on_following_posts: false
    });

    // Main header resize function
    function resize_header() {
        const hn = document.querySelector("#header-nav");
        const sidebar = document.querySelector("#side-bar");
        if (hn !== null) {
            if (window.innerWidth > 660) {
                hn.style.width = window.innerWidth - sidebar.offsetWidth + 'px';
            } else {
                const hn = document.querySelector("#header-nav");
                hn.style.width = window.innerWidth + "px";
            }
        }
    }

    function setAllCurrent() {
        const all_posts_div = document.querySelector(`#${all_posts_id}`);
        const following_posts_div = document.querySelector(`#${following_posts_id}`);
        all_posts_div.style.display = 'block';
        following_posts_div.style.display = 'none';
        setState({
            name: "Homepage",
            on_all_posts: true,
            on_following_posts: false
        })
    }

    function setFollowingCurrent() {
        const all_posts_div = document.querySelector(`#${all_posts_id}`);
        const following_posts_div = document.querySelector(`#${following_posts_id}`);
        all_posts_div.style.display = 'none';
        following_posts_div.style.display = 'block';
        setState({
            name: "Following",
            on_all_posts: false,
            on_following_posts: true
        })
    }

    useEffect(() => {
        setAllCurrent();
        resize_header();
        // After first resize
        window.addEventListener('resize', resize_header);
    }, [])
    

    return(

        <>
            <nav>
                <div className="home-header" id="header-nav">
                    <div className="home-title-div">
                        <div className="home-title">{state.name}</div>
                    </div>
                    <div className="home-tab-div">

                        {user ? (
                            <>
                            <div onClick={setAllCurrent} id="AllPosts" className="home-tab">All Posts

                                {state.on_all_posts ?
                                    (
                                    <div className="blue-bar"></div>
                                    ) : (
                                        <></>
                                    )}
                            </div>

                            <div onClick={setFollowingCurrent} id="FollowingPosts" className="home-tab">Following

                                {state.on_following_posts ?
                                    (
                                    <div className="blue-bar"></div>
                                    ) : (
                                        <></>
                                    )}
                            </div>
                            </>
                        ) : (
                            <div onClick={setAllCurrent} id="AllPosts" className="home-tab">All Posts
                            
                                {state.on_all_posts ?
                                    (
                                    <div className="blue-bar"></div>
                                    ) : (
                                        <></>
                                    )}
                            </div>
                        )}

                    </div>
                </div>
            </nav>
        </>

    );

}

export default HeaderNav;