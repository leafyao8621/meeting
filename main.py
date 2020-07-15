import time
import meetingscheduler
import scheduler

def main():
    meetingscheduler.initialize()
    meetingscheduler.reset(100, 10000)
    start = time.time()
    num = meetingscheduler.schedule(0, "")
    end = time.time()
    print(f"C Extension:\nnum: {num}")
    print(f"runtime: {end - start}")
    scheduler.initialize()
    start = time.time()
    scheduler.schedule(0, "")
    end = time.time()
    print(f"Pure Python:\nnum: {num}")
    print(f"runtime: {end - start}")
    scheduler.finalize()
    meetingscheduler.finalize()

if __name__ == "__main__":
    main()
