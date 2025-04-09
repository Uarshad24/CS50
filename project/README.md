# Personal Portfolio Website
#### Video Demo: https://youtu.be/sTnLr6Ey0I8
#### Description:

This project is a personal portfolio designed to showcase my skills, experience, and projects in the field of Data Science and Machine Learning. It provides a user-friendly interface with sections like "About Me," "Skills," "Certifications," "Education," "Portfolio," and "Contact," each carefully crafted to present my achievements and professional journey. The website is built using HTML, CSS, and JavaScript to create an interactive and visually appealing experience for users.

This portfolio serves as a medium to highlight my abilities as a Data Scientist and Machine Learning Engineer, featuring projects I've worked on, such as image classification, time series analysis, and future explorations into recommendation systems. By using a clean, responsive design, the site adapts well to both desktop and mobile views.

### Project Structure

The project consists of the following files:

**index.html:** The main HTML file that contains the structure of the portfolio website.It also includes the JavaScript for interactive features like tab navigation and mobile side menu handling.\
**style.css:** The CSS file responsible for the styling and layout of the website.\
**js/custom.js:** The JavaScript file used for customizing the particles effect background.\
**js/particles.min.js:** A JavaScript file for a particles effect used in the background .\
**files/Resume.pdf:** A downloadable resume that visitors can access to get a more detailed view of my professional qualifications.

### index.html

This is the core HTML structure of the portfolio. It contains sections such as:

**Header Section:** Displays the main introduction with my name, navigation bar, and an interactive background.\
**About Me Section:** Provides a brief introduction about me, including my skills, certifications, and education details. Tabs are used for navigation between these sub-sections, making the page interactive. Also includes download CV button.\
**Portfolio Section:** Showcases the projects I've worked on, each linked to a GitHub repository or a description of the work.\
**Contact Section:** Displays my contact details like email and phone number, along with social media icons linking to my LinkedIn, GitHub, Kaggle, and Medium profiles.\
**JavaScript:** This JavaScript handles several dynamic elements on the page:
- **Tab Navigation:** When a user clicks on the "Skills," "Certifications," or "Education" tabs, this script ensures the active tab is highlighted and the corresponding content is displayed.
- **Side Navigation Menu:** It provides the functionality for opening and closing the side navigation on smaller screens. This helps maintain a clean layout on mobile devices.

### style.css

This CSS file handles all the styling of the website. It ensures a clean, modern look while maintaining readability and accessibility. The styles have been designed with responsiveness in mind, so the layout adjusts smoothly on different screen sizes.

Key features in the CSS include:

**Color Scheme:** The dark background color (#080808) with white and accents of pink (#ff004f) for a clean, professional appearance.\
**Grid System:** The use of Flexbox and CSS Grid for creating responsive layouts that adapt to various screen sizes, such as the portfolio section and the navigation menu.\
**Hover Effects:** Interactive hover effects for navigation links and portfolio items, making the website feel dynamic and user-friendly.\
**Media Queries:** Ensures that the website is mobile-friendly by adjusting font sizes, layout configurations, and hiding certain elements for smaller screens (e.g., side menu toggles).

### js/custom.js
The custom.js file in this project is responsible for handling the particle effect in the background. The particles appear to float and move randomly, creating an engaging, interactive background for the user. Here’s a brief breakdown of how the particles effect works:

**Particle Count and Density:** The number of particles is set to 380, and their density is controlled within a defined area (value_area: 3000).\
**Particle Color and Shape:** The particles are white (color: #ffffff) and are shaped as circles. A polygonal shape can also be used with a defined number of sides, or images can be used (e.g., GitHub logo), though the default is circular.\
**Opacity and Size:** Particles have a slight opacity of 0.5, giving them a soft and subtle look. Their size is randomized between values, with the default size being 3.\
**Interactivity:** The particles react to user interaction: On hover, particles are "grabbed" by the mouse, causing them to pull toward the cursor. On click, particles are "pushed," creating a slight burst effect with new particles being generated. Additionally, particles are linked with lines, forming a network of connected particles, which can enhance the background’s aesthetic appeal.\
**Movement:** The particles move at a speed of 0.9, and they exit the screen when reaching the edge (out_mode: "out"). The movement is designed to be fluid and seamless.

### js/particles.min.js

This is a third-party script used to create a subtle particles effect in the background of the header. It enhances the visual appeal and adds interactivity to the website, making the page feel more dynamic. The particles are lightweight and do not significantly impact performance.

### files/Resume.pdf
This is the downloadable resume file. It contains a detailed breakdown of my education, experience, skills, and certifications. Users can easily download it to review my qualifications in more depth. The link to the resume is provided in the "About Me" section.

### Design Choices

**Responsive Design**
One of the key design choices for this project was ensuring it would work seamlessly on both desktop and mobile devices. Using Flexbox and CSS Grid made it easy to create layouts that adjust based on screen size. The side navigation menu only appears as a hamburger menu on small screens, ensuring the website remains clean and easy to navigate on mobile devices.

**Interactive Tabs**
The "Skills," "Certifications," and "Education" sections are organized using tabs. This feature allows users to toggle between the sub-sections without needing to reload the page. The use of JavaScript enables this interaction, making the website more engaging and improving the user experience.

**Color Scheme and Typography**
I selected a dark background color for the website to create a sleek, modern look that highlights the white text and accent colors. The accent color, #ff004f, was chosen for its vibrancy and to ensure key elements like links and buttons stand out. I used the 'Poppins' font for its clean, modern appearance, which improves readability.

**Hover Effects and Transitions**
Subtle hover effects were added to the navigation links and portfolio items to provide a more interactive feel. The transition effects make the website feel polished and responsive. For example, when users hover over portfolio project items, the background color changes, and they slightly lift, giving a sense of depth and making the site feel more dynamic.

**Accessibility**
Ensuring accessibility was also a priority. The color contrast between the dark background and white text provides sufficient readability, and the layout is designed to be easily navigable on all devices, including screen readers. Additionally, the website avoids excessive use of animations, which can be distracting or inaccessible to some users.

### Conclusion
This portfolio website is an essential part of my personal brand as a Data Scientist and Machine Learning Engineer. It effectively showcases my skills, qualifications, and projects, and its modern, responsive design ensures an optimal user experience across devices. I’ve used a combination of HTML, CSS, and JavaScript to create a dynamic and interactive portfolio, and I’ve ensured that the website is both aesthetically pleasing and easy to navigate.
