# Thread
## I. Giới thiệu chung
### 1. Nguyên lý hoạt động
- Tương tự như process, thread được tạo ra với mục đích xử lý đồng thời hiều công việc cùng một lúc (mutil-task).
- Một thread là một lightweight process có thể được quản lý độc lập bởi một bộ lập lịch.
- Trên một hệ thống mutil-core. Nhiều threads có thể hoạt động song song.
- Nếu một thread bị block, các thread khác vẫn hoạt động bình thường.
- Mỗi khi một thread được tạo, chúng sẽ được đặt trong stack segments. \
![image](ThreadinStack.png)
### 2. Context switching
![image](ContextSwitching.png) 
### 3. so sánh Thread với Process
1. Context switching time
- Process cần nhiều thời gian hơn vì chúng nặng hơn.
- Thread cần ít thời gian hơn vì chúng nhẹ hơn process.
2. Shared Memory
- Chia sẻ dữ liệu giữa các tiến trình là khó khăn hơn. Thông qua các cơ chế IPC
- Các thread trong một process có thể chia sẻ dữ liệu với nhau nhanh chóng và dễ dàng.
3. Crashed
- Nếu một process bị crashed, process khác vẫn thực thi bình thường.
- Nếu một thread bị crashed, các threads khác chấm dứt ngay lập tức.
4. Thread ID
- Cũng giống như một tiến trình được xác định bởi một process ID, một thread trong process được xác định bởi một thread ID. 
- Cần phải làm rõ một vài điểm sau:
\- Process ID là duy nhất trên toàn hệ thống, trong đó thread ID là duy nhất trong một tiến trình (process). \
\- Process ID là một giá trị số nguyên nhưng thread ID không nhất thiết phải là một giá trị số nguyên. Nó có thể là một structure. \
\- Process ID có thể được in ra rất dễ dàng trong khi thread ID thì không.
## II. Thao tác với Thread
### 1. Tạo một Thread mới
``` C
int pthread_create(pthread_t *threadID, const pthread_attr_t *attr, void *(*start)(void *), void *arg);
/*

*/
```
### 2. Lấy giá trị Thread ID
``` C
pthread_t pthread_self(void);
/*

*/
```
### 3. So sánh 2 Thread
``` C
int pthread_equal(pthread_t tid1, pthread_t tid2);
/*

*/
```
### 4. Kết thúc một Thread
``` C
void pthread_exit(void *retval);
/*

*/
```
## II. thread management
### 1. Quản lý Thread
1. Thread Termination 
- Thread kết thúc một cách bình thường.
\- Thread kết thúc khi gọi hàm pthread_exit().
\- Thread bị hủy bỏ khi gọi hàm pthread_cancel(). 
\- Bất cứ một thread nào gọi hàm exit(), hoặc main thread kết thúc thì tất cả các thread còn lại kết thúc ngay lập tức.
``` C
int pthread_exit(void *retval);
```
``` C
int pthread_cancel(pthread_t thread);
```
2. Joinable Thread
- Để thu được giá trị kết thúc của một thread khác ta sử dung pthread_join().
- Hoạt động này được gọi là joining.
- pthread_join() sẽ block cho đến khi một thread kết thúc (threadID được truyền vào đối số thread). Nếu thread đó đã kết thúc thì pthread_join return ngay lập tức.  
- `` note `` \
\- Khi thread kết thúc, về cơ bản nó sẽ được xử lý như tương tự như một zombie process. Nếu số lượng zombie thread ngày càng lớn. Một lúc nào đó ta sẽ không thể tạo thêm thread được nữa. Vai trò của pthread_join() tương tự với waitpid().

``` C
int pthread_join(pthread_t thread, void **retval);
/*
thread:  ThreadID của một thread cụ thể.
**retval: Nếu retval khác NULL, nó sẽ nhận được giá trị trả về của pthread_exit().
Trả về 0 nếu thành công, nhỏ hơn 0 nếu thất bại
*/
```
3. Detaching a Thread
- Mặc định, một thread là joinable , tức là khi thread kết thúc thì một thread khác có thể thu được giá trị trả về của thread đó thôn qua pthread_join().
- Tuy nhiên, nhiều trường hợp chúng ta không cần quan tâm về trạng thái kết thúc của thread mà chỉ cần hệ thống tự động clean và remove thread một cách tự động.
- Trường hợp này chúng ta có thể đặt thread vào trạng thái detached thông qua việc gọi pthread_detached()
- ``note`` \
\- Một khi thread bị detached, ta không thể dùng pthread_join() để thu được trạng thái kết thúc của thread, và thread không thể trở về trạng thái joinable.

``` C
int pthread_detach(pthread_t thread);
/*
    thread:  ThreadID của một thread cụ thể.
    Trả về 0 nếu thành công, nhỏ hơn 0 nếu thất bại.
*/
```

### 2. Thread Synchronization
- Một trong các điểm mạnh của thread đó chính là việc chia sẻ dữ liệu với nhau thông qua các biến global.
- Tuy nhiên, nó sẽ tồn tại một số vấn đề về đồng bộ.
- Điều gì sẽ xảy ra nếu nhiều thread cùng sửa một biến vào cùng một thời điểm? Hay một thread đang cố đọc giá trị của một biến trong khi thread khác đang sửa đổi biến đó?
1. Atomic/ Nonatomic
- Atomic: Tại một thời điểm chỉ có một thread duy nhất được truy cập vào tài nguyên được chia sẻ (shared resource). Vì vậy, atomic an toàn.
- Nonatomic: Nhiều threads có thể truy cập vào shared resource cùng một thời điểm. Vì vậy, nonatomic không an toàn.

2. Crictical Section
- Thuật ngữ critical section được dùng để chỉ đoạn code truy cập vào vùng tài nguyên được chia sẻ giữa (shared resource) giữa các threads và việc thực thi của nó nằm trong bối cảnh atomic. Tức là, thời điểm đoạn code được thực thi sẽ không bị gián đoạn bởi bất cứ một thread nào truy cập đồng thời vào shared resource đó.

### 3. Thread - Mutex
1. Mutex
- Mutex (mutual exclusion) là một kĩ thuật được sử dụng để đảm bảo rằng tại một thời điểm chỉ có 1 thread mới có quyền truy cập vào các tài nguyên dùng chung (shared resources).
- Việc triển khai mutex nhìn chung thực hiện qua 3 bước:
\- Khởi tạo khóa mutex
\- Thực hiện hiện khóa mutex cho các shared resource trước khi vào critical section.
\- Thực hiện truy cập vào shared resources.
\- Mở khóa/giải phóng khóa mutex.
2. Allocated Mutexes
- Khóa mutex là một biến kiểu pthread_mutex_t. Trước khi sử dụng thì ta luôn phải khởi tạo khóa mutex.
- Khóa mutex có thể được cấp phát tĩnh hoặc động.
``` C
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER; // Cấp phát tĩnh
int pthread_mutex_t(pthread_mutex_t *mutex, const pthread_mutexattr_t *atrr); // cấp phát động
/*

*/
```
- ``note`` \
\- Khi không sử dụng ta phải hủy mutex bằng pthread_mutex_destroy(). Khởi tạo tĩnh thì không cần phải gọi hàm này.
3. Locking and Unlocking a Mutex
- Sau khi khởi tạo,  khóa mutex rơi vào trạng thái unlocked.
- Để  lock hoặc unlock một khóa mutex ta sử dụng hai hàm pthread_mutex_lock() và pthread_mutex_unlock().
``` C
int pthread_mutex_lock(pthread_mutex_t *mutex);
/*
    *mutex: Con trỏ tới khóa mutex
    Trả về 0 nếu thành công, nhỏ hơn 0 nếu thất bại
*/
int pthread_mutex_unlock(pthread_mutex_t *mutex);
/*
    *mutex: Con trỏ tới khóa mutex
    Trả về 0 nếu thành công, nhỏ hơn 0 nếu thất bại.
*/
```
- ``note`` \
\- Khi khóa mutex ở trạng thái unlocked, pthread_mutex_lock() sẽ return ngay lập tức. Ngược lại, nếu mutex đang locked bởi một thread khác thì pthread_mutex_lock() sẽ bị block cho tới khi mutex được unlocked.

4. Mutex Deadlocks
- Hiện tượng một thread khóa một mutex và không thể thoát ra được được gọi là mutex deadlock.


### 4. Thread Sync - Condition Variables
1. Condition Variables 
- Một mutex được sử dụng việc truy cập vào shared variable cùng một thời điểm.
- Một condition variable được sử dụng để thông báo tới một thead khác về sự thay đổi của một shared variable và cho phép một thread khác block cho tới khi nhận được thông báo.

2. Allocated Condition Variables 
- Condition variable là một biến kiểu pthread_cond_t. Trước khi sử dụng thì ta luôn phải khởi tạo nó.
- Condition variable có thể được cấp phát tĩnh hoặc động.
``` C
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int pthread_cond_init(pthread_cond_t *cond, const pthread_condattr_t *attr);
/*

*/
```
- Khi không sử dụng ta phải hủy condition variable bằng pthread_cond_destroy (). Khởi tạo tĩnh thì không cần phải gọi hàm này.

3. Signaling/Waiting trên Condition Variables 
- Hai hoạt động chính của condition variable là signal và wait.
``` C
int pthread_cond_signal(pthread_cond_t *cond);
int pthread_cond_broadcast(pthread_cond_t *cond);
int pthread_cond_wait(pthread_cond_t *cond, pthread_mutex_t *mutex);
```

