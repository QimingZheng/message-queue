# message-queue

stl的设计是只支持并发读的

queue_map[xxx].push操作有可能新增加一个关键字，导致hash列表长度变化，某些情况下致使边界的读写越界


最后的目标是1.5kw量级的消息并发读写能在3s内完成
