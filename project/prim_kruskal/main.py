import tkinter as tk
import math
from prim import prim
from kruskal import kruskal

entries = []
start_entry = None
frame2 = None
start_frame = None
submit_btn = None

INF = 999

def focus_next_in_row(event, i, j, n):
    if j + 1 < n:
        entries[i][j + 1].focus_set()
    elif i + 1 < n:
        entries[i + 1][0].focus_set()
    else:
        start_entry.focus_set()
    return "break"


def focus_down_column(event, i, j, n):
    if i + 1 < n:
        entries[i + 1][j].focus_set()
    else:
        start_entry.focus_set()
    return "break"


def get_matrix(n):
    global start_entry, frame2, start_frame, submit_btn
    frame1.destroy()
    frame2 = tk.Frame(root)
    frame2.pack()

    tk.Label(frame2, text="Enter matrix elements: ").pack()

    for i in range(n):
        row_frame = tk.Frame(frame2)
        row_frame.pack()
        tk.Label(row_frame, text=f"Row {i+1}:").pack(side="left")
        row_entries = []
        for j in range(n):
            e = tk.Entry(row_frame, width=5)
            e.pack(side="left")
            e.bind("<Return>", lambda ev, i=i, j=j: focus_next_in_row(ev, i, j, n))
            e.bind("<Control-Return>", lambda ev, i=i, j=j: focus_down_column(ev, i, j, n))
            row_entries.append(e)
        entries.append(row_entries)

    start_frame = tk.Frame(root)
    start_frame.pack(pady=10)
    tk.Label(start_frame, text="Enter starting node (0-indexed):").pack(side="left")
    start_entry = tk.Entry(start_frame, width=5)
    start_entry.pack(side="left")
    start_entry.bind("<Return>", lambda ev: (submit_matrix(), "break")[1])

    submit_btn = tk.Button(root, text="SUBMIT", command=submit_matrix)
    submit_btn.pack()

    entries[0][0].focus_set()


def get_rows(event=None):
    n = int(entry_rows.get())
    get_matrix(n)


def draw_matrix(canvas, A, x, y, title):
    canvas.create_text(x, y, text=title, anchor="nw", font=("Arial", 12, "bold"))
    y += 25
    cell = 60  # cell width
    for i, row in enumerate(A):
        for j, val in enumerate(row):
            cx, cy = x + j * cell, y + i * cell
            canvas.create_rectangle(cx, cy, cx + cell, cy + cell)
            canvas.create_text(cx + cell / 2, cy + cell / 2, text=str(val), font=("Arial", 10))


def node_positions(n, cx, cy, radius):
    """Place n nodes evenly around a circle, return {label: (x, y)}."""
    pos = {}
    for i in range(n):
        angle = 2 * math.pi * i / n - math.pi / 2
        x = cx + radius * math.cos(angle)
        y = cy + radius * math.sin(angle)
        pos[i + 1] = (x, y)  # labels 1..n
    return pos


def draw_graph(canvas, A, x, y, title, radius=110, highlight_edges=None):
    highlight_edges = highlight_edges or set()
    n = len(A)
    canvas.create_text(x, y, text=title, anchor="nw", font=("Arial", 12, "bold"))

    cx, cy, r = x + radius + 20, y + radius + 60, radius
    pos = node_positions(n, cx, cy, r)

    # edges (skip 0 = self / no-edge, and INF = no-edge sentinel)
    for i in range(n):
        for j in range(n):
            w = A[i][j]
            if i == j or w == 0 or w >= INF:
                continue
            x1, y1 = pos[i + 1]
            x2, y2 = pos[j + 1]
            undirected = (i + 1, j + 1) in highlight_edges or (j + 1, i + 1) in highlight_edges
            color = "red" if undirected else "gray"
            width = 3 if color == "red" else 1
            canvas.create_line(x1, y1, x2, y2, arrow=tk.LAST,
                                fill=color, width=width)
            mx, my = (x1 + x2) / 2, (y1 + y2) / 2
            canvas.create_text(mx, my, text=str(w), fill=color,
                                font=("Arial", 9))

    # nodes (drawn after edges so they sit on top)
    for label, (nx, ny) in pos.items():
        canvas.create_oval(nx - 15, ny - 15, nx + 15, ny + 15,
                            fill="lightblue", outline="black")
        canvas.create_text(nx, ny, text=str(label))

    return cy + r  # bottom edge of the drawn graph, for layout below it


def mst_edges_and_cost(mst_matrix):
    """
    Extract undirected edges + total weight from an MST adjacency matrix.
    Assumes prim()/kruskal() each return a matrix same shape as the input,
    with 0 meaning 'no edge' and only edges belonging to the MST carrying
    their weight. Handles both symmetric and single-direction-filled
    matrices.
    """
    n = len(mst_matrix)
    seen = set()
    edges = []
    total = 0
    for i in range(n):
        for j in range(n):
            w = mst_matrix[i][j]
            if i == j or w == 0 or w >= INF:
                continue
            key = frozenset((i, j))
            if key in seen:
                continue
            seen.add(key)
            edges.append((i + 1, j + 1, w))
            total += w
    return edges, total


def draw_solution_text(canvas, edges, total, x, y, title):
    canvas.create_text(x, y, text=title, anchor="nw", font=("Arial", 12, "bold"))
    y += 25
    for a, b, w in sorted(edges):
        canvas.create_text(x, y, anchor="nw", font=("Arial", 10),
                            text=f"Edge {a}-{b}: weight={w}")
        y += 22
    y += 8
    canvas.create_text(x, y, anchor="nw", font=("Arial", 10, "bold"),
                        text=f"Total MST cost: {total}")
    return y + 25


def draw_algo_panel(canvas, A, mst_matrix, x, y, algo_title):
    """Draws one algorithm's mini graph + edge list block, starting at (x, y)."""
    edges, total = mst_edges_and_cost(mst_matrix)
    tree_edges = {(a, b) for a, b, _ in edges}
    graph_bottom = draw_graph(canvas, A, x, y, algo_title, radius=85,
                               highlight_edges=tree_edges)
    draw_solution_text(canvas, edges, total, x, graph_bottom + 25, "Edges & Cost")


def submit_matrix():
    global frame2, start_frame, submit_btn

    A = [[int(e.get()) for e in row] for row in entries]
    start = int(start_entry.get())
    prim_mst_matrix = prim(A, start)
    kruskal_mst_matrix = kruskal(A, start)

    frame2.destroy()
    start_frame.destroy()
    submit_btn.destroy()

    canvas_frame = tk.Frame(root, width=1400, height=950)
    canvas_frame.pack(fill="both", expand=True)
    canvas = tk.Canvas(canvas_frame, width=1380, height=950, bg="white",
                        scrollregion=(0, 0, 1380, 950))
    canvas.pack(fill="both", expand=True)

    # panel 1: raw matrix
    draw_matrix(canvas, A, x=20, y=20, title="Given Matrix")

    # panel 2: graph form (plain)
    draw_graph(canvas, A, x=420, y=20, title="Graph Form", radius=110)

    # panel 3 & 4: side-by-side algorithm results
    canvas.create_text(20, 400, text="Prim's MST", anchor="nw",
                        font=("Arial", 13, "bold"))
    draw_algo_panel(canvas, A, prim_mst_matrix, x=20, y=430, algo_title="Prim")

    canvas.create_text(700, 400, text="Kruskal's MST", anchor="nw",
                        font=("Arial", 13, "bold"))
    draw_algo_panel(canvas, A, kruskal_mst_matrix, x=700, y=430, algo_title="Kruskal")


root = tk.Tk()
root.title("PRIM & KRUSKAL")
root.geometry("1400x950")

frame1 = tk.Frame(root)
frame1.pack()

tk.Label(frame1, text="Enter the no of rows in matriix:").pack()

entry_rows = tk.Entry(frame1)
entry_rows.pack()
entry_rows.bind("<Return>", get_rows)

tk.Button(frame1, text="NEXT", command=get_rows).pack()

root.mainloop()