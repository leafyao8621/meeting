import meetingscheduler

def main():
    meetingscheduler.initialize()
    meetingscheduler.reset(100, 100)
    print(meetingscheduler.schedule(1, "stdout"))
    meetingscheduler.finalize()

if __name__ == "__main__":
    main()
