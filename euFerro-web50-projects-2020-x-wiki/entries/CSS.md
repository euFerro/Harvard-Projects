# CSS

##### Cascading Style Sheets, is a language used to describe the presentation of HTML and XML documents. It provides a set of rules that define how the elements of a web page should be styled and displayed to users. The main components of CSS include:
    
## Selectors
##### CSS selectors are used to target specific HTML elements and apply styles to them. There are several types of selectors in CSS, including element selectors, class selectors, ID selectors, attribute selectors, and more:
        
### Element selector
##### Targets elements based on their tag name, for example
* p
* h1

### Class selector
##### Targets elements based on the value of their class attribute, for example:
* .my-class

### ID selector
##### Targets elements based on the value of their ID attribute, for example:
* #my-id

### Universal selector (*)
##### Targets all elements on the page, for example:
* *

### Attribute selector
##### Targets elements based on the value of their attributes, for example:
* [type="text"]

### Child selector
###### Targets elements that are direct children of another element, for example:
* ul > li

### Descendant selector:
##### Targets elements that are descendants of another element, for example:
* ul li

### Adjacent sibling selector
##### Targets elements that are immediately adjacent to another element, for example:
* h + p

### General sibling selector: Targets elements that are siblings of another element, for example:
* h ~ p

### Pseudo-class selector
##### Targets elements based on a certain state. Pseudo-class selectors are predefined and cannot be created. They are a set of selectors that are used to target elements based on their state or behavior, such as:
* :hover
* :active
* :focus
* :visited
* :first-child
* :last-child
* :nth-child()
* and more...

### Pseudo-element selector
##### Targets parts of an element, such as ::before and ::after.
* ::before: This pseudo-element is used to insert content before the content of an element. It is often used to add decorative content, such as icons or separators, to an element.
* ::after: This pseudo-element is used to insert content after the content of an element. It is often used to add additional text or decorative content to an element.

### Properties
##### CSS properties define the style and layout of an element. There are hundreds of CSS properties that can be used to modify the appearance of text, backgrounds, borders, margins, padding, and more.

### Values
##### CSS values define the specific settings for a CSS property. For example, the font-size property can be set to a specific size value such as "*px", "*em", or "**m". CSS supports a variety of units of measurement, including:
* Pixel (px): This is a fixed unit of measurement that always stays the same size, regardless of the screen size or zoom level.
* Percentage (%): This unit of measurement is relative to the parent container. For example, setting the width of a div to *% will make it half the width of its parent container.
* Viewport Height (vh) and Viewport Width (vw): These units are relative to the viewport size (the visible area of the browser window). For example, setting the height of a div to *vh will make it half the height of the viewport.
* em: This unit is based on the font-size of the parent element. For example, setting the font-size of a paragraph to **m will make the font **times larger than the font-size of its parent element.
* rem: This unit is based on the font-size of the root element (the <html> element). For example, setting the font-size of the root element to *px and the font-size of a paragraph to **em will make the font-size of the paragraph *px (**times *px).
* Absolute (in, cm, mm, pt, pc): These units are fixed physical units of measurement that are based on physical dimensions such as inches, centimeters, millimeters, points, etc.
* Viewport Percentage (vmin and vmax): These units are relative to the viewport size, but they take the smaller or larger value of the height or width, depending on which is smaller or larger.
* These are the most commonly used units of measurement in CSS, but there are also other less common units, such as ch, ex, and fr.
* Variables are also known as custom properties, and they allow you to define a value once and reuse it throughout your stylesheet. CSS variables are defined using the -- prefix and can be accessed using the var() function.

##### Here is an example of how to define and use a CSS variable:
In this example, the --main-color variable is defined on the :root pseudo-class, which represents the root element of the document (usually the <html> element). The h*element then uses the var() function to set its color property to the value of the --main-color variable.

## Box model
##### The box model is a concept in CSS that defines how elements are laid out on a web page. It consists of four properties: margin, border, padding, and content. These properties define the space around and within an element.
 
## Cascade
##### The cascade is the process by which CSS styles are applied to elements on a web page. When multiple styles are defined for an element, the cascade determines which styles take precedence based on a set of rules.

## Specificity
##### Specificity is a measure of how specific a CSS selector is. When multiple selectors target the same element, the one with the highest specificity will take precedence.
* Inline
* #id
* .class
* element
* Inheritance: Inheritance is the process by which CSS styles are passed down from parent elements to their child elements. This allows for consistent styling across a web page or site.				

## Viewport
##### In CSS, the viewport refers to the area of the browser window that is currently visible to the user. It is the part of the screen that displays the web page content, and it can vary in size depending on the device and screen resolution.
To ensure that web pages are displayed correctly on different devices and screen sizes, developers can use the viewport meta tag in the HTML head section. This tag allows developers to control the size and scaling of the viewport, which affects how the web page content is displayed. The viewport meta tag has several attributes that developers can use to control the viewport, including:
* width: Sets the width of the viewport to a specific value or device width.
* initial-scale: Sets the initial zoom level of the viewport.
* minimum-scale: Sets the minimum zoom level of the viewport.
* maximum-scale: Sets the maximum zoom level of the viewport.
* user-scalable: Controls whether users can zoom in and out of the web page content.
By using the viewport meta tag, developers can ensure that their web pages are displayed correctly and consistently across different devices and screen sizes. This is especially important for responsive web design, which aims to provide a seamless user experience across desktops, tablets, and smartphones.

## Flexbox
##### Flexbox is a layout module in CSS that allows developers to create flexible and responsive layouts for web pages. With flexbox, you can arrange elements in a container along a single axis (either horizontally or vertically) and control their spacing, alignment, and order. Flexbox is based on the concept of flex containers and flex items. A flex container is any HTML element that has the display: flex or display: inline-flex property set. This container holds one or more flex items, which are the child elements of the container.
With flexbox, you can use a variety of properties to control the layout of the flex items inside the container. Some of the most commonly used flexbox properties include:
* justify-content: Controls the horizontal alignment of flex items inside the container.
* align-items: Controls the vertical alignment of flex items inside the container.
* flex-direction: Controls the direction of the main axis inside the container (either row or column).
* flex-wrap: Controls whether flex items should wrap onto multiple lines when the container is too narrow.
* flex-basis: Sets the initial size of a flex item before any remaining space is distributed.
* flex-grow: Specifies how much a flex item should grow relative to the other flex items in the container.
* flex-shrink: Specifies how much a flex item should shrink relative to the other flex items in the container.

By using these properties, developers can create flexible and responsive layouts that adapt to different screen sizes and devices. Flexbox has become a popular choice for building modern web layouts, due to its simplicity and flexibility.
Grid
CSS Grid is a layout module in CSS that allows developers to create two-dimensional grid layouts with rows and columns for designing web pages. With CSS Grid, developers can create complex grid layouts without the need for nested HTML structures or floats, making it a more efficient and flexible layout system.
CSS Grid works by dividing a web page into a grid container, which contains one or more grid items. Grid items can be positioned anywhere on the grid using a combination of row and column lines, which are defined using CSS Grid properties.
Some of the key properties used in CSS Grid include:
* display: grid: Defines the element as a grid container.
* grid-template-columns and grid-template-rows: Define the size and number of columns and rows in the grid.
* grid-column-start, grid-column-end, grid-row-start, and grid-row-end: Define the position of grid items on the grid.
* grid-column and grid-row: Shorthand properties for setting the start and end positions of grid items.
* grid-gap: Defines the space between grid rows and columns.

Using these properties, developers can create a wide range of grid layouts, from simple two-column designs to complex multi-row and multi-column layouts. CSS Grid is well-supported by modern browsers, making it a powerful tool for creating responsive and flexible web page layouts.
Media Query
Media queries in CSS are used to apply different styles to a web page based on the characteristics of the device or screen that it is being viewed on. With media queries, developers can create responsive designs that adapt to different screen sizes and devices, providing a better user experience for their audience. Media queries work by specifying a set of conditions that must be met for the styles to be applied. These conditions are based on various characteristics of the device or screen, such as its width, height, orientation, and resolution. For example, to apply a different background color to a web page when it is viewed on a mobile device, you could use the following:  
Media queries are used in CSS to apply different styles to a web page depending on the characteristics of the device or screen that it's being viewed on, such as screen width, height, orientation, and resolution. Here's how to use media queries in CSS:
* Define the media query: Start by specifying the media type and the conditions under which the styles should be applied. For example, to target screens with a maximum width of **pixels, use the following:

* Add the styles: Within the media query block, add the CSS styles that should be applied when the conditions are met. For example:

In this example, when the screen width is less than or equal to **pixels, the font size of the body element is set to * pixels, and the header element is hidden.
* Add multiple media queries: You can define multiple media queries to target different screen sizes and devices. For example:

In this example, three media queries are defined to target small, medium, and large screens.
Media queries are a powerful tool in CSS for creating responsive web designs that adapt to different devices and screen sizes. By using media queries, you can provide an optimal user experience for your visitors, regardless of the device they're using.
Animations
There are several ways animations can be created in CSS:
* CSS Transitions: CSS transitions allow you to animate the changes in CSS properties smoothly over a specified duration. You can define a transition for a specific property such as color, background-color, height, width, etc.
You can use transitions to animate any change in a CSS property. For example, here is an example of a transition applied to a class:

* CSS Animations: CSS Animations allow you to create more complex and dynamic animations. With CSS animations, you can define keyframes that describe how the animation should change over time. (example in the end of the article)
* CSS Transform: CSS Transform allows you to transform elements in * or * space by changing their position, size, or shape. You can also use CSS Transforms with CSS Animations to create more complex animations.
* SVG Animations: SVG Animations allow you to create complex and vector-based animations using CSS or JavaScript. You can animate the stroke, fill, and other SVG attributes.
* JavaScript Animations: JavaScript Animations give you more control over the animation process. You can use JavaScript libraries such as jQuery or GreenSock to create complex animations and interactions. However, JavaScript animations require more coding and can be more complex than CSS-based animations.
Overall, there are many ways to create animations in CSS, each with their own strengths and weaknesses.
Keyframes
Keyframes in CSS are used to define the intermediate steps in an animation. They allow you to specify the values of CSS properties at specific points during the animation.
Keyframes are defined using the @keyframes rule, which specifies a name for the animation and the values of CSS properties at specific percentages of the animation's duration. Here's an example:

In this example, the @keyframes rule defines an animation called myAnimation. The animation will change the opacity of an element from * to **. The first keyframe, defined with *, specifies that the opacity should be *at the beginning of the animation. The second keyframe, defined with *%, specifies that the opacity should be **halfway through the animation. The third keyframe, defined with **, specifies that the opacity should be *at the end of the animation.
Once you have defined keyframes, you can use them in an animation by applying the animation name to an element using the animation-name property. You can also specify:
* animation-duration: Specifies the duration of the animation in seconds or milliseconds.
* animation-timing-function: Specifies the timing function that should be used to control the acceleration and deceleration of the animation.
* animation-delay: Specifies the delay before the animation starts.
* animation-iteration-count: Specifies the number of times the animation should be repeated.
* animation-direction: Specifies whether the animation should play in a forward, backward, or alternate direction.
* animation-fill-mode: Specifies how the element should be styled before and after the animation.
* animation-play-state: Specifies whether the animation is running or paused.
Here is an example that shows how some of these properties can be used together: