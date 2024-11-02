<h1>minishell</h1>

<h2>Description</h2>

Minishell is a project aimed at creating a minimal shell in C, simulating the functionality of the <code>bash</code> terminal. This shell provides a basic interface for executing commands and managing environment variables, maintaining an interactive user experience.

<h2>Core Functionalities</h2>
<ul>
  <li><strong>Interactive Prompt</strong>: The shell displays a prompt when waiting for a new command.</li>
  <li><strong>Command History</strong>: A command history is available for previously executed commands.</li>
  <li><strong>Command Search and Execution</strong>: Minishell can execute commands found in the <code>PATH</code> environment variable or by using relative or absolute paths.</li>
  <li><strong>Environment Variable Handling</strong>: Supports expansion of environment variables (e.g., <code>$USER</code>) and the exit status of the last executed command (<code>$?</code>).</li>
  <li><strong>Quote Handling</strong>: Supports single (<code>'</code>) and double (<code>"</code>) quotes to prevent the interpretation of metacharacters within quoted sequences.</li>
   <li><strong>Pipes</strong>: Supports pipelines (<code>|</code>), where the output of each command in the pipeline is connected to the input of the next.</li>
</ul>
  <h4>Redirections:</h4>
    <ul>
      <li><code>&lt;</code> for input redirection.</li>
      <li><code>&gt;</code> for output redirection.</li>
      <li><code>&gt;&gt;</code> for appending output to a file.</li>
      <li><code>&lt;&lt;</code> with a delimiter to read input until the specified delimiter line is reached. (heredoc)</li>
    </ul>
  
  <h4>Built-in Commands</h4>
    <ul>
      <li><code>echo</code> with <code>-n</code> option.</li>
      <li><code>cd</code> with only relative or absolute paths.</li>
      <li><code>pwd</code> with no options.</li>
      <li><code>export</code>, <code>unset</code>, <code>env</code>, and <code>exit</code> without options.</li>
    </ul>

<h2>Compilation Instructions</h2>

Type <strong><code>make</code></strong> to generate the executable <strong><code>minishell</code></strong>

