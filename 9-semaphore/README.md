# Semaphore 
## I. Giới thiệu
1. giới thiệu
- Semaphore là cơ chế cho phép đồng bộ truy cập giữa các process và thread.
- Mục đích chính được sử dụng để block process và thread truy cập vào 1 vùng nhớ (shared memory) mà đang được sử dụng bởi một process/thread khác.
- Có 2 loại semaphore được sử dụng dụng chủ yếu: 
\- System V semaphore
\- POSIX semaphore
2. Posix Semaphore?
Được đưa ra bởi SUSv3 bao gồm có 2 loại như sau:
- Named semaphores: 
    * Là semaphore được đặt tên, được tạo open thông quan việc sử dụng hàm sem_open(). Các unrelated-process có thể truy cập tới cùng một semaphore. 
- Unnamed semaphores:
    * Là semaphore không được đặt tên, do không có name để sử dụng chung nên để sử dụng nó cần phải truy cập vào các vùng nhớ dùng chung (shared memory, mmap(), global variable …)
    * Được sử dụng cho việc chia sẻ truy cập giữa các Process hoặc các Thread.
    * Đối với các process thì nó là vùng nhớ được shared (sử dụng system shm hoặc POSIX mmap), còn với thread là vùng nhớ mà các thread được chia sẻ trong chương trình ví dụ: global hoặc head.

## II. Semaphore Operations
### 1. Hoạt động
- Semaphore là một số nguyên được duy trì bởi kernel có giá trị bị hạn chế lớn hơn hoặc bằng 0. 
- Có thể thực hiện nhiều hoạt động khác nhau (tức là các lệnh gọi hệ thống) trên semaphore, bao gồm những điều sau:
\- Tăng giá trị hiện tại của semaphore lên 1 dùng sem_post.
\- Trừ giá trị hiện tại của semaphore xuống 1 dùng sem_wait().
\- Đọc giá trị hiện tại của semaphore.
### 2. Waiting on semaphore
- Hàm sem_wait () giảm (giảm 1) giá trị của semaphore
- Nếu semaphore hiện có giá trị lớn hơn 0, sem_wait () trả về ngay lập tức. 
- Nếu giá trị của semaphore hiện là 0, sem_wait () sẽ block cho đến khi giá trị semaphore tăng trên 0.
- Sau khi sem_wait() được trả về thì giá trị của semaphore sẽ được giảm đi 1.
``` C

```
- Hàm sem_trywait() là một phiên bản non-blocking của hàm sem_wait().
``` C

```
- Hàm sem_timedwait() Chỉ thực hiện chờ trong một thời gian nhất định, nếu sau timeout mà giá trị semaphore vẫn bằng 0 thì lỗi sẽ được trả về ETIMEDOUT.
``` C

```
### 3. Posting on semaphore
- Hàm sem_post () tăng (tăng 1) giá trị của semaphore.
``` C

```
- Nếu giá trị của semaphore bằng 0 thì thực hiện tăng giá trị của semaphore value lên 1. Khi đó các process đang chờ sem_wait() sẽ được đánh thức.
- Nếu có nhiều process cùng đang chờ thì kernel sử dụng thuật toán round-robin, time-sharing để quyết đinh. 
- Tức là không phải process là wait trước sẽ được thực hiện trước mà sau khi sem_post() thì process nào là time slot (time slice) tiếp theo của CPU thì sẽ được thực hiện.

### 4. Read semaphore value
- Hàm sem_getvalue() trả về giá trị hiện tại của semaphore
``` C

```
- Giá trị semaphore được trả về trong con trỏ sval.

## III. Named Semaphore
### 1. Opening named semaphore 
- sem_open() được sử dụng để tạo một semaphore mới hoặc mở một semaphore đang tồn tại.
``` C

```
- name: tên định danh semaphore. Mỗi tên liên kết với một semaphore object.
- oflag: cho biết mode hoạt động của sem_open().
\- 0: mở một semaphore đang tồn tại.
\- O_CREAT: tạo một semaphore mới.
\- O_CREAT và O_EXCL: tạo một semaphore mới và trả về lỗi nếu đã tồn tại semaphore liên kết với tên được đưa ra
- Nếu O_CREAT được sử dụng thì 2 đối số nữa sẽ được dùng cho sem_open()
\- mode: giá trị quyền của semaphore được tạo ra, giống như set quyền cho file (ví dụ full quyền r/w 0666).
\- value: giá trị khởi tạo cho semaphore, là nguyên (>=0). 

### 2. Closing named semaphore 
- Khi thực hiện sem_open() thì semaphore sẽ được liên kết với process. Hệ thống sẽ ghi lại mối liên kết này.
- sem_close() sẽ thực hiện kết thúc mối liên kết trên. Giải phóng bất kỳ tài nguyên nào mà hệ thống đã liên kết với semaphore cho process và giảm số lượng các process tham chiếu đến semaphore.
``` C

```
### 3. Removing named semaphore
- Hàm sem_unlink () xóa semaphore được xác định bằng name và đánh dấu semaphore sẽ bị hủy sau khi tất cả các process ngừng sử dụng nó.
- Tức là semaphore sẽ bị hủy khi tất cả tiến trình sử dụng nó gọi sem_close().
``` C

```
## IV. Unnamed Semaphore
### 1. Initializing an unnamed semaphore
- Hàm sem_init() được sử dụng để khởi tạo semaphore và inform cho kernel semaphore được sử dụng để shared giữa các process hoặc giữa các thread trong một process.
- Đối số pshared cho biết liệu semaphore có được chia sẻ giữa các threads hay giữa các process hay không.
``` C

```
\- pshared là 0: thì semaphore sẽ được chia sẻ giữa các thread của process. sem được tạo ra trỏ tới một địa chỉ của heap hoặc global.
\- pshared khác 0: semaphore được shared giữa các process. sem sẽ là địa chỉ của một vùng nhớ được shared giữa các process (system V hoặc Posix mmap).
\- value: giá trị semaphore được khởi tạo.

### 2. Destroying an unnamed semaphore
- Hàm sem_destroy() hủy semaphore, nó phải là một unnamed semaphore đã được khởi tạo trước đó bằng sem_init(). 
- Sau khi một unnamed semaphore đã bị hủy bằng sem_destroy(), nó có thể được khởi động lại bằng sem_init().
``` C

```