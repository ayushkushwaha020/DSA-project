# Student Record Management System — DSA Mini Project

A student-record application demonstrating core Data Structures and Algorithms.

## Live web application
This repository contains a static browser-based dashboard suitable for Vercel deployment. Open `index.html` locally, or deploy the repository to Vercel.

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

## Deploy on Vercel
1. Import this GitHub repository into Vercel.
2. Select **Other** as the framework preset if asked.
3. Leave the build command and output directory empty/default (the site is static at the repository root).
4. Deploy.

## Original C console project
The `student_record_system.c` file is the standalone C implementation for compiling and running in a terminal:

```bash
gcc student_record_system.c -o student_record_system
./student_record_system
```
On Windows, run `student_record_system.exe`.

## Notes
The browser version is a visual, interactive demonstration of the DSA behaviours. Its linked list and stack are maintained in JavaScript at runtime; browser local storage persists the visible records and requests. The C source is the console implementation for the DSA practical submission.
