<!DOCTYPE html>
<html>
<head>
    <style>
        body {
            background: linear-gradient(to right, #ff7e5f, #feb47b); /* Gradient background */
            color: #fff; /* White text for contrast */
            font-family: Arial, sans-serif;
            padding: 20px;
        }
        h1, h2, h3, h4, h5, h6 {
            color: #333;
        }
        pre {
            background-color: #222;
            color: #f8f8f2;
            padding: 10px;
            border-radius: 5px;
        }
    </style>
</head>
<body>
    <h1>Transaction Management System</h1>

    <img src="https://media.giphy.com/media/3o6gE5kY7wzQpMoC6g/giphy.gif" alt="Welcome Image" style="width: 100%; max-height: 200px; object-fit: cover;">
    <p><em>Welcome to the Transaction Management System!</em></p>

    <h2>Table of Contents</h2>
    <ol>
        <li><a href="#project-overview">Project Overview</a></li>
        <li><a href="#features">Features</a></li>
        <li><a href="#installation">Installation</a></li>
        <li><a href="#usage">Usage</a></li>
        <li><a href="#file-structure">File Structure</a></li>
        <li><a href="#modules">Modules</a></li>
        <li><a href="#future-enhancements">Future Enhancements</a></li>
        <li><a href="#developer">Developer</a></li>
    </ol>

    <h2 id="project-overview">Project Overview</h2>
    <p>The <strong>Transaction Management System</strong> is a stellar application crafted to handle and manage financial transactions and account data with ease. It supports saving, loading, and managing transactions and account states, offering a seamless user experience for various operations such as reporting stolen cards and processing transactions.</p>

    <h2 id="features">Features</h2>
    <ul>
        <li><strong>Transaction Handling</strong>: Swiftly processes and stores transactions, supporting various states like <code>APPROVED</code>, <code>DECLINED</code>, and more.</li>
        <li><strong>Account Management</strong>: Manages account data, including balance and state (<code>RUNNING</code>, <code>BLOCKED</code>).</li>
        <li><strong>Data Persistence</strong>: Saves and loads transaction and account data to/from CSV files.</li>
        <li><strong>Interactive Console Application</strong>: Engages users with an intuitive console interface for managing transactions and handling card operations.</li>
    </ul>

    <h2 id="installation">Installation</h2>
    <p>Get your project up and running on your local machine with these steps:</p>
    <ol>
        <li><strong>Clone the repository</strong>:
            <pre><code>git clone https://github.com/yourusername/transaction-management-system.git</code></pre>
        </li>
        <li><strong>Navigate to the project directory</strong>:
            <pre><code>cd transaction-management-system</code></pre>
        </li>
        <li><strong>Compile the project</strong>:
            <pre><code>gcc -o transaction_management main.c handling.c app.c -I./include</code></pre>
        </li>
        <li><strong>Run the application</strong>:
            <pre><code>./transaction_management</code></pre>
        </li>
    </ol>

    <h2 id="usage">Usage</h2>
    <ol>
        <li><strong>Start the Application</strong>: Execute the compiled file to launch the transaction management system.</li>
        <li><strong>Perform Transactions</strong>: Follow the on-screen instructions to carry out transactions or report a stolen card.</li>
        <li><strong>Save & Load Data</strong>: The system handles data persistence, saving and loading automatically.</li>
        <li><strong>Exit the Application</strong>: Close the application anytime, with all data securely saved.</li>
    </ol>

    <h2 id="file-structure">File Structure</h2>
    <pre><code>
transaction-management-system/
├── Handling/
│   ├── handling.c
│   ├── handling.h
├── app/
│   ├── app.c
│   ├── app.h
├── include/
│   ├── handling.h
│   ├── app.h
├── main.c
├── transactions.csv
├── accountDB.csv
└── README.md
    </code></pre>

    <h2 id="modules">Modules</h2>
    <h3>Main Module</h3>
    <p><strong>File</strong>: <code>main.c</code></p>
    <p><strong>Description</strong>: The heart of the application, managing the entire flow, initializing data, and handling user interactions.</p>

    <h3>Handling Module</h3>
    <p><strong>File</strong>: <code>handling.c</code>, <code>handling.h</code></p>
    <p><strong>Description</strong>: Responsible for saving, loading, and managing transaction and account data, including file operations and data conversion.</p>

    <h3>Application Module</h3>
    <p><strong>File</strong>: <code>app.c</code>, <code>app.h</code></p>
    <p><strong>Description</strong>: Manages core logic such as transaction processing and card reporting, ensuring smooth operations.</p>

    <h2 id="future-enhancements">Future Enhancements</h2>
    <ul>
        <li><strong>Improved Security</strong>: Add encryption for sensitive data stored in CSV files.</li>
        <li><strong>Enhanced User Interface</strong>: Develop a graphical user interface for a better user experience.</li>
        <li><strong>Reporting & Analytics</strong>: Include features for generating reports and analytics on transaction history and account statuses.</li>
    </ul>

    <h2 id="developer">Developer</h2>
    <p>This project was developed with care by <a href="https://github.com/amrkhaled104">Amr Khaled</a>. Explore my GitHub profile for more amazing projects and contributions!</p>
    <img src="https://media.giphy.com/media/26tPpjCcsDEjc0Lz6/giphy.gif" alt="Developer Image" style="width: 100%; max-height: 200px; object-fit: cover;">
</body>
</html>
