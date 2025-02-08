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
key_t ftok(const char *pathname, int proj_id);
/*
    @param[pathname] : file path 
    @param[proj_id]  : id của key
*/
```
2. Tạo Shared Memory segment
- Mỗi segment được liên kết với một structure về permission cho việc read/write của process.
- Trong đó mode là một tổ hợp bitwise.
- Để tạo shared memory segment sử dụng API  shmget().
``` C
int shmget(key_t key, size_t size, int shmflg)
/*
    @param[in] key Identifier key
    @param[in] size The size of the shared memory segment rounded to multiple of PAGE_SIZE
    @param[in] shmflg mode flags
        IPC_CREAT --> Creating new segment. if the segment associated with this key already
                                   exists, use the existing segment.
        IPC_EXCL  --> Create new segment. if the segment already exists, the call fails.
    @return Shared memory ID if OK, −1 on error
*/
```
3. Attach/detach vùng shared memory
- Attach shared memory segment tới một địa chỉ bộ nhớ của chương trình đang gọi.
- Để làm được điều này chúng ta sử dụng API shmat().
- Để detach vùng nhớ của process khỏi shared memory segment chúng ta sử dụng API shmdt().
- Lệnh này không xóa identifier và structure của nó khỏi hệ thống. Identifier sẽ tồn tại đến khi một tiến trình trong hệ thống gọi shmctl với IPC_RMID command.
``` C
int shmdt(const void shmaddr)
/*
    @brief Detaching the shared memory segment from the address space of the calling process
      
    @param[in] shmaddr The address of shared memory segment to be detached, returned by the shmat()
        system call this command does not remove shared memory ID and structure from 
        the system shared memory ID will persist until a process in the system calls
        shmctl with the IPC_RMID command.
    @return 0 if OK, −1 on error
*/  
```
4. Giải phóng shared memory segment
- API shmctl() được sử dụng để kiểm soát các hoạt động của shared memory segment.
- Chúng ta thường sử dụng system call này cùng với command IPC_RMID để giải phóng hoàn toàn shared memory segment trên hệ thống.
``` C
int shmctl(int shmid, int cmd, struct shmid_ds buf)
/*
    @brief Control operation for a System V shared memory segment
    @param[in] shmid Shared memory ID
    @param[in] cmd 
        IPC_STAT --> Copies the information of the current values of each member of struct shmid_ds 
                              to the passed structure pointed by buf. This command requires read permission to
                              the shared memory segment.
        IPC_SET  --> Sets the user ID, group ID of the owner, permissions, etc. pointed to by structure buf
        IPC_RMID --> Marks the segment to be destroyed. The segment is destroyed only after the last process
                    has detached it.
        IPC_INFO -->  Returns the information about the shared memory limits and parameters in the structure
                    pointed by buf.
        SHM_INFO --> Returns a shm_info structure containing information about the consumed system resources
                              by the shared memory.
    @param[in] buf Pointer to the shared memory structure named struct shmid_ds. The values of this structure would be 
                sed for either set or get as per cmd.
*/
```
### III. POSIX Shared Memory
1. Tạo shared memory object
- Ở System V shared memory chúng ta có khái niệm shared memory segment. Trong khi đó, ở POSIX chúng ta có khái niệm shared memory object.
- Cả hai khái niệm trên đều là tương đương và ám chỉ về một vùng nhớ chia sẻ được giữa các process.
- Để tạo một shared memory object chúng ta sử dụng API shm_open().
``` C
/*
    int shm_open (const char name, int oflag, mode_t mode);
    @param[in] name File path
    @param[in] oflag 
        O_RDONLY --> process open shared memory object với quyền ReadOnly.        
        O_RDWR   --> process open shared memory object với quyền Read/Write.
        O_CREAT  --> tạo shared memory segment nếu không tồn tại.
        O_EXCL   --> nếu như shared memory object với file được đưa ra đang tồn tại thì trả về lỗi EEXIST.
        O_TRUNC  --> nếu shared memory object đang tồn tại thực hiện truncate tới giá trị 0.
    @param[in] mode permission của shared memory object được tạo. Nếu oflag không sử dụng cờ O_CREAT hay 
                shared memory object đang tồn tại thì mode sẽ bị bỏ qua.
                       
    @return Sau khi tạo thành công thì có thể thấy file liên kết với shared memory trong đường dẫn, -1 nếu lỗi.
*/
```
2. Set size
- Khi shared memory object được tạo ra. Kích thước của nó được khởi tạo bằng 0.
- Do đó ta cần phải set size cho shared memory object thông qua API ftruncate().
``` C
int ftruncate (int shm_fd, off_t length);
/*
    @brief Configure the size of the shared memory object.
             After opening, the size of the shared memory object is 0     
    @param[in] shm_fd shm file descriptor
    @param[in] length the size (in bytes) of shared memory object

    @return
*/ 
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
int munmap(void addr, size_t length);
/*
    @brief Unmap shared memory object khỏi calling process.
      
    @param[in] addr địa chỉ memory của calling process được map.
    @param[in] length độ dài của shared memory object được map (> 0).
      
    @return On success, munmap() returns 0. 
              On failure, it returns -1, and errno is set to 
              indicate the cause of the error (probably to EINVAL).
*/ 
```
4. Giải phóng shared memory object
- Để giải phóng shared memory object được tạo ra trước đó chúng ta sử dụng API shm_unlink().
- Shared memory object sẽ được xóa sau khi process cuối cùng được unmap.
``` C
int shm_unlink(const char *name);
/*
    @param[name] : path name 
*/ 
```

