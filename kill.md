    SIGINT: interrupt signal, by ctrl-c, orderly graceful shutdown and can be caught and ignored
    SIGQUIT: dump core signal, by ctrl-\,  abort the process, can be caught and ignored
    SIGTERM: termination signal, can by caught or ignored
    SIGKILL: kill signal, process can not catch the signal, cannot cleanup
    SIGSTOP: pause signal, pause the process, cannot be caught or ignored
