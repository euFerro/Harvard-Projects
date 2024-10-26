import { useState, useEffect } from 'react';
import './Homepage.css';
import './Loading.css';
import HeaderNav from "../components/HeaderNav";
import PostForm from "../components/PostForm";
import Post from '../components/Post';


function Homepage() {

    const [allPosts, setAllPosts] = useState([]);
    const [followingPosts, setFollowingPosts] = useState([]);
    const [is_loading, setLoading] = useState(false);
    const [allPostsCounter, setAllPostsCounter] = useState(0);
    const [followingPostsCounter, setFollowingPostsCounter] = useState(0);

    const user = JSON.parse(localStorage.getItem('logged_user'));
    // if  (user !== undefined) {
    //     console.log(user);
    // }
    
    function set_top_offset() {
        const header_nav = document.querySelector('#header-nav');
        const homepage = document.querySelector('#Homepage');
        homepage.style.paddingTop = header_nav.offsetHeight + 'px';
    }

    function getPosts(counter, queryString) {
        // console.log('GET ALL POSTS');
        const start = counter * 10;
        const end = start + 10;
        
        setLoading(true);
        fetch(`/posts?q=${queryString}&start=${start}&end=${end}`, {
            "method": "GET"
        })
        .then(response => response.json())
        .then(response => {

            if (response.error) {
                alert(`(!) Error - ${response.error}`);
                return false;
            } else {
                const posts = JSON.parse(response);
                // console.log(posts);
                if (queryString === 'all-posts') {
                    setAllPosts(posts);
                }
                if (queryString === 'following-posts') {
                    setFollowingPosts(posts);
                }
            }
            setLoading(false);
            return false;
        });
    }

    function changePage(homepageTabName, cmd) {
        if (homepageTabName === 'allPosts') {
            if (cmd === 'next') {
                setAllPostsCounter(allPostsCounter + 1);
            }
            if (cmd === 'prev') {
                if (allPostsCounter === 0) {
                    return
                }
                setAllPostsCounter(allPostsCounter - 1);
            }
        }
        if (homepageTabName === 'followingPosts') {
            if (cmd === 'next') {
                setFollowingPostsCounter(followingPostsCounter + 1);
            }
            if (cmd === 'prev') {
                if (followingPostsCounter === 0) {
                    return;
                }
                setFollowingPostsCounter(followingPostsCounter - 1);
            }
        }
    }

    let prevBtnAllPostsClassName = "pagination-btn prev-btn";
    let prevBtnFollowingPostsClassName = "pagination-btn prev-btn";

    if (allPostsCounter === 0) {
        prevBtnAllPostsClassName = "pagination-btn prev-btn inactive";
    }
    if (followingPostsCounter === 0) {
        prevBtnFollowingPostsClassName = "pagination-btn prev-btn inactive";
    }

    useEffect (() => {
        document.title = 'Home - Social Network';

        set_top_offset();

        getPosts(allPostsCounter, 'all-posts');
        getPosts(followingPostsCounter, 'following-posts');

    }, [allPostsCounter, followingPostsCounter]);

    return(
        <>
            <HeaderNav all_posts_id={'all-posts-div'} following_posts_id={'following-posts-div'} user={user}/>

            <div id='Homepage'>
                
                {user ? (
                    <PostForm user={user}/>
                ) : (
                    <></>
                )}

                <div id="all-posts-div">

                    {is_loading ? (
                        <div className='loading-container'>
                            <div className="lds-ring"><div></div><div></div><div></div><div></div></div>
                        </div>
                    ) : (
                        <></>
                    )}

                    {allPosts.map(post => {
                        return <Post
                            key={post.key}
                            post={post}    
                        />;
                    })}

                    {allPosts.length === 0 ? (
                        <div className='nothing-here'>Nothing here yet.</div>
                    ) : (
                        <></>
                    )}

                    <div className='pagination-footer'>
            
                        <div onClick={() => changePage('allPosts', 'prev')} className={prevBtnAllPostsClassName}>
                            prev
                        </div>
                        <div onClick={() => changePage('allPosts', 'next')} className='pagination-btn next-btn'>
                            next
                        </div>

                        <div className='mx-2'>Page: {allPostsCounter + 1}</div>
                    </div>

                </div>

                <div id="following-posts-div">

                    {is_loading ? (
                        <div className='loading-container'>
                            <div className="lds-ring"><div></div><div></div><div></div><div></div></div>
                        </div>
                    ) : (
                        <></>
                    )}

                    {followingPosts.map(post => {
                        return <Post
                            key={post.key}
                            post={post}
                        />;
                    })}
                    
                    {followingPosts.length === 0 ? (
                        <div className='nothing-here'>Nothing here yet.</div>
                    ) : (
                        <></>
                    )}

                    <div className='pagination-footer'>

                        <div onClick={() => changePage('followingPosts', 'prev')} className={prevBtnFollowingPostsClassName}>
                            prev
                        </div>
                        <div onClick={() => changePage('followingPosts', 'next')} className="pagination-btn next-btn">
                            next
                        </div>

                        <div>Page: {followingPostsCounter + 1}</div>
                    </div>

                </div>

            </div>

        </>     
    );
}

export default Homepage;