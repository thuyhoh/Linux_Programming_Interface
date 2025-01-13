# Signal in Linux
## I. Giới thiệu
### 1. Định nghĩa
- Signal là một trong những phương thức dùng để giao tiếp liên tiến trình lâu đời nhất của Unix System.
- Signal là một software interrupt, là cơ chế xử lý các sự kiện bất đồng bộ (async).
- ví dụ \
\- Những sự kiện này có thể bắt nguồn từ bên ngoài như khi người dùng nhấn tổ hợp phím Ctrl+C. Hoặc từ các hoạt động trong chương trình như phép chia một số cho 0.
### 2. Signal Lifecycle
- Generation: Đầu tiên một tín hiệu signal được raised/sent/generated.
- Delivery: Một signal được pending cho tới khi nó được phân phối.
- Processing: Một khi tín hiệu được phân phối, nó có thể được xử lý bởi nhiều cách. \
\- Ignore the signal: Không action nào được thực hiện. SIGKILL và SIGSTOP không thể bị ignore.
\- Catch and handle the signal: Kernel sẽ tạm dừng thực thi main thread và nhảy tới hàm xử lý signal được user đăng kí trong process (signal handler). SIGINT và SIGTERM là hai signal thường được dùng. SIGKILL và SIGSTOP không thể catch.
\- Perform the default action: hành động này đã được định nghĩa săn 

![signal Processing](Signal_Processing.png)
## II. Signal Handler
- Chúng ta đăng kí việc xử lý một signal thông qua system call signal().
- Signal là một software interrupt nên nó khá nhạy cảm về mặt thời gian thực thi. Khi signal handler được thực thi nó sẽ chiếm hoàn toàn cpu của process. Cần phải thoát ra hàm xử lý signal nhanh nhất có thể.

## III. Một số signal cơ bản
- SIGKILL   : 	Chỉ có thể gửi bằng system call kill(). Process không thể caught hoặc ignored. Mặc định sẽ kết thúc tiến trình được chỉ định.
- SIGTERM: 	Chỉ có thể gửi bằng system call kill(). Mặc định sẽ kết thúc tiến trình được chỉ định, tuy nhiên process có thể catch tín hiệu này và dọn dẹp trước khi kết thúc.
- SIGINT    : 	Tín hiệu này được gửi tới các process trong nhóm foreground process. Mặc định sẽ kết thúc tiến trình hiện tại.
- SIGCHLD: 	Bất cứ khi nào một tiến trình dừng lại, nó sẽ gửi SIGCHLD tới process cha của nó. Mặc định SIGCHLD bị ignored.
- SIGSTOP : 	Chỉ có thể gửi bằng system call kill(). Process không thể caught hoặc ignored. Mặc định sẽ tạm dừng process được chỉ định.
- SIGUSR1/SIGUSR2: Signals có sẵn cho người dùng tự định nghĩa.

## IV. Sending Signals
- Signal có thể gửi được qua hàm system call kill() trong mã nguồn.
- Ngoài ra có thể gửi thông qua command kill trên terminal. Có thể tự gửi signal đến bản thân tiến trình đó thông qua việc sử dụng hàm getpid().
``` C
int kill (pid_t pid, int signo);
```




