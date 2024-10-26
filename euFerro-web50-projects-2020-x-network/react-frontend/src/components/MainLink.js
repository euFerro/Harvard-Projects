import "./MainLink.css"
import { Link, useMatch, useResolvedPath } from "react-router-dom";

function MainLink({id, name, img_source, url, have_img, have_name}) {

    const resolvedPath = useResolvedPath(url);
    const isActive = useMatch({ path: resolvedPath.pathname, end: true});

    return (
        <>
            <div className={isActive ? "side-item-div active" : "side-item-div"} id={id}>

                <div className="side-item">
                    <Link className="side-item" to={url}>

                        {have_img ? (
                            <img
                            width="32px"
                            height="32px"
                            src={img_source}
                            alt=''
                            />
                        ) : (
                            <></>
                        )}

                        {have_name ? (
                            <span className="side-item hide-small">{name}</span>
                        ) : (
                            <></>
                        )}
                    </Link>
                </div>

            </div>
        </>
    );

}

export default MainLink;