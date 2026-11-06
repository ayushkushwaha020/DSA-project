# Student Record Management System — DSA Mini Project

A student-record application demonstrating core Data Structures and Algorithms.

## Live web application

**Render deployment:** https://dsa-project-98gw.onrender.com

The application is hosted on Render and connected to this repository's `main` branch. New commits to `main` are configured to trigger automatic deployments.

## DSA concepts
| Concept | Use | Complexity |
|---|---|---|
| Singly Linked List | Dynamic student record storage | Traversal O(n) |
| Stack | Undo recent record changes (LIFO) | Push/pop O(1) |
| Circular Queue | Process service requests (FIFO) | Enqueue/dequeue O(1) |
| Linear Search | Search by name, course or roll number | O(n) |
| Merge Sort | Sort by name or marks | O(n log n) |

## Features
- Add, edit, delete and search student records
- Sort students by name or marks using merge sort
- Undo the latest record mutation
- Add and process student service requests in FIFO order
- Dashboard statistics: total students, average, pass percentage and pending requests
- Browser local storage keeps the web demo's data on the current device

## Run locally
No build step or package installation is required. Open `index.html` in a browser.

## Render deployment
This is a static site deployed from the repository root.
- **Repository:** https://github.com/ayushkushwaha020/DSA-project
- **Branch:** `main`
- **Build command:** none
- **Publish directory:** `.`
- **Auto-deploy:** enabled

## Original C console project
The `student_record_system.c` file is the standalone C implementation for compiling and running in a terminal:

```bash
gcc student_record_system.c -o student_record_system
./student_record_system
```
On Windows, run `student_record_system.exe`.

## Notes
The browser version is a visual, interactive demonstration of the DSA behaviours. Its linked list and stack are maintained in JavaScript at runtime; browser local storage persists the visible records and requests. The C source is the console implementation for the DSA practical submission.
