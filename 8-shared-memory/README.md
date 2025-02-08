# Shared memory
## I. Giới thiệu
- Shared memory là vùng nhớ cho phép cho phép nhiều tiến trình có thể cùng truy cập tới. 
- Làm tăng tốc độ xử lý khi các tiến trình không cần gửi gửi nhận dữ liệu cho nhau.
- Sau khi được tạo vùng nhớ ảo của chương trình sẽ nằm trong khoảng không gian địa chỉ giữa vùng nhớ  head và vùng nhớ stack.
- Có 2 phương pháp để tạo shared memory: 
\- sử dụng API của shm (System V)
\- sử dụng API của mmap (POSIX).
- ưu điểm
- nhược điểm
## II. System V Shared Memory
#### Anonymous Mapping (mapping vùng nhớ trên RAM)
1. Tạo key.
- Shared memory segment được kernel quản lý bởi một IPC structure. Mỗi IPC structure sẽ được xác định bởi một sô nguyên (không âm) Identifier.
- Để có thể map/đọc/ghi dữ liệu vào shared memory thì các process cần phải biết được các số Identifier này.
- Indentifier có thể được tạo ra thông qua API ftok()
``` C

```
2. Tạo Shared Memory segment
- Mỗi segment được liên kết với một structure về permission cho việc read/write của process.
- Trong đó mode là một tổ hợp bitwise.
- Để tạo shared memory segment sử dụng API  shmget().
``` C

```
3. Attach/detach vùng shared memory
- Attach shared memory segment tới một địa chỉ bộ nhớ của chương trình đang gọi.
- Để làm được điều này chúng ta sử dụng API shmat().
- Để detach vùng nhớ của process khỏi shared memory segment chúng ta sử dụng API shmdt().
- Lệnh này không xóa identifier và structure của nó khỏi hệ thống. Identifier sẽ tồn tại đến khi một tiến trình trong hệ thống gọi shmctl với IPC_RMID command.
``` C

```
4. Giải phóng shared memory segment
- API shmctl() được sử dụng để kiểm soát các hoạt động của shared memory segment.
- Chúng ta thường sử dụng system call này cùng với command IPC_RMID để giải phóng hoàn toàn shared memory segment trên hệ thống.
``` C

```
### III. POSIX Shared Memory
1. Tạo shared memory object
- Ở System V shared memory chúng ta có khái niệm shared memory segment. Trong khi đó, ở POSIX chúng ta có khái niệm shared memory object.
- Cả hai khái niệm trên đều là tương đương và ám chỉ về một vùng nhớ chia sẻ được giữa các process.
- Để tạo một shared memory object chúng ta sử dụng API shm_open().
``` C

```
2. Set size
- Khi shared memory object được tạo ra. Kích thước của nó được khởi tạo bằng 0.
- Do đó ta cần phải set size cho shared memory object thông qua API ftruncate().
``` C

```
3. Map/unmap shared memory object
- Để map shared memory object vào trong vùng nhớ của process chúng ta cần sử dụng API mmap(). 
- Kĩ thuật này còn được gọi là memory mapping.
- Chúng ta có 4 kiểu memory mapping như sau:
\- Private anonymous mapping.
\- Shared anonymous mapping.
\- Private file mapping.
\- Shared file mapping.
- Để upmap chúng ta sử dụng API munmap().
``` C

```
4. Giải phóng shared memory object
- Để giải phóng shared memory object được tạo ra trước đó chúng ta sử dụng API shm_unlink().
- Shared memory object sẽ được xóa sau khi process cuối cùng được unmap.
``` C

```

