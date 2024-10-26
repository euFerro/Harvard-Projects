import { useEffect, useState } from "react";
import Post from "../components/Post";
import BackBar from "../components/BackBar";


export default function Likedpage() {
    const [isLoading, setLoading] = useState(true);
    const [paginationCounter, setPaginationCounter] = useState(0);
    const [posts, setPosts] = useState([]); 

    let prevBtnClassName = "pagination-btn prev-btn";

    if (paginationCounter === 0) {
        prevBtnClassName = "pagination-btn prev-btn inactive";
    }

    function changePage(cmd) {
        if (cmd === 'next') {
            setPaginationCounter(paginationCounter + 1);
        }
        if (cmd === 'prev') {
            if (paginationCounter === 0) {
                return;
            }
            setPaginationCounter(paginationCounter - 1);
        }
    }

    function getPosts() {
        const start = paginationCounter * 10;
        const end = start + 10;
        
        setLoading(true);
        fetch(`/posts?q=liked-posts&start=${start}&end=${end}`, {
            "method": "GET"
        })
        .then(response => response.json())
        .then(response => {

            if (response.error) {
                alert(`(!) Error - ${response.error}`);
                return false;
            } else {
                const posts = JSON.parse(response);
                setPosts(posts);
            }
            setLoading(false);
        });
    }

    useEffect(() => {
        document.title = "Liked Posts - Social Network";
        getPosts();
    }, [paginationCounter]);

    return (
        <>
            <BackBar title={"Liked Posts"}/>

            <div id="all-posts-div">

                    {isLoading ? (
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
                        <div className="nothing-here">Nothing here yet.</div>
                    ) : (
                        <></>
                    )}

                    <div className='pagination-footer'>
                                
                        <div onClick={() => changePage('prev')} className={prevBtnClassName}>
                            prev
                        </div>
                        <div onClick={() => changePage('next')} className='pagination-btn next-btn'>
                            next
                        </div>

                        <div className='mx-2'>Page: {paginationCounter + 1}</div>
                    </div>

                {}
            </div>
        </>
    );
}