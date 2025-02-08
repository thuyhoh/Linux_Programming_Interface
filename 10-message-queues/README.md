# Message Queues

## I. Giới thiệu
### 1. Message Queues là gì?
- Một Message Queues là một danh sách liên kết (link-list) các message được duy trì bởi kernel.
- Tất cả các process có thể trao đổi dữ liệu thông qua việc truy cập vào cùng một queues.
- Mỗi một message sẽ được đính kèm thông thêm thông tin về type (type message).
- Dựa vào type message mà các process có thể lấy ra tin nhắn phù hợp.

## II. System V Message Queues
### 1. Tạo key
- Key được sử dụng có thể là một số nguyên bất kì hoặc được tạo ra bởi hàm ftok().
### 2. Create a message queue
- Để tạo mới hoặc mở một message queues đã tồn tại chúng ta sử dụng msgget().
\- key: key được tạo từ bước 1
\- msgflg:
    * IPC_CREAT
    * IPC_EXCL 
- Trả về message id của message queue nếu thực hiện thành công.
### 3. Write into message queue
- Để ghi dữ liệu (send/append) vào message queue chúng ta sử dụng msgsnd().
\- msqid: message id thu được từ msgget().
\- msgp: con trỏ tới message (send).
\- msgsz: kích thước message.
\- msgflg: 
    * IPC_NOWAIT: Return ngay lập tức nếu message trong queue đã full. 
    * MSG_NOERROR: Cắt bớt message nếu kích thước mess lớn hơn msgsz.

### 3 Read from the message queue
- Để đọc dữ liệu từ message queue chúng ta sử dụng msgrcv().
\- msqid: message id thu được từ msgget().
\- msgp: con trỏ tới buffer (read).
\- maxmsgsz: thường là kích thước của buffer.
\- msgtyp: 0, +ve hoặc –ve.
\- msgflg: 
    - IPC_NOWAIT: Return ngay lập tức nếu không tìm thấy message trong queue. 
    - MSG_NOERROR: Cắt bớt message nếu kích thước mess lớn hơn maxmsgsz.
### 4 Delete message queue
- Để kiểm soát các hoạt động trên message queue chúng ta sử dụng msgctl().
\- msqid: message id thu được từ msgget().
\- cmd:
    - IPC_RMID: Xóa message queue ngay lập tức.
    - IPC_STAT
    - IPC_SET
- Để xóa một message queue thông thường cmd chúng ta dùng là IPC_RMID và  buf để thành giá trị NULL.

## III. POSIX Message Queues
### 1. Opening a message queue
- Để tạo mới hoặc mở một message queues đã tồn tại chúng ta sử dụng mq_open().
\- name: Tên message queue
\- oflag: 
    - O_CREATE
    - O_EXCL
    - O_RDONLY
    - O_NONBLOCK
\- mode: 0666
\- attr: Chỉ định các thuộc tính của message queue. Nếu là NULL sẽ sử dụng các thuộc tính mặc định.
### 2 Sending message
- Để ghi dữ liệu vào message queue chúng ta sử dụng mq_send().
\- mqdes: mq descriptor được trả về ở 3.1
\- msg_ptr: con trỏ tới message.
\- msg_len: kích thước message.
\- msg_prio: priority của message.

### 3 Receving message
- Đọc dữ liệu từ message queue chúng ta sử dụng mq_receive().
\- mqdes: mq descriptor được trả về ở 3.1
\- msg_ptr: con trỏ tới message.
\- msg_len: kích thước message.
\- msg_prio: priority của message.
- Hàm mq_receive () loại bỏ message có mức độ ưu tiên cao nhất khỏi queue, được tham chiếu bởi mqdes và trả về thông báo đó trong bộ đệm do msg_ptr trỏ tới.
### 4 Clossing a message queue
- Để đóng message queue khi không còn sử dụng ta sử sử dụng mq_close().
\- mqdes: mq descriptor được trả về ở 3.1.

### 5 Remove a message queue
- Để xóa message queue khi không còn sử dụng ta sử sử dụng mq_ unlink().

