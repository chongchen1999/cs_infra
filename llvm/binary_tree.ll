; ModuleID = 'binary_tree.c'
source_filename = "binary_tree.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

%struct.Node = type { i32, %struct.Node*, %struct.Node* }

@.str = private unnamed_addr constant [26 x i8] c"Memory allocation failed\0A\00", align 1
@.str.1 = private unnamed_addr constant [4 x i8] c"%d \00", align 1
@.str.2 = private unnamed_addr constant [21 x i8] c"In-order traversal: \00", align 1
@.str.3 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@.str.4 = private unnamed_addr constant [13 x i8] c"Deleting 20\0A\00", align 1
@.str.5 = private unnamed_addr constant [22 x i8] c"Searching for 40: %s\0A\00", align 1
@.str.6 = private unnamed_addr constant [6 x i8] c"Found\00", align 1
@.str.7 = private unnamed_addr constant [10 x i8] c"Not found\00", align 1
@.str.8 = private unnamed_addr constant [23 x i8] c"Searching for 100: %s\0A\00", align 1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local %struct.Node* @createNode(i32 noundef %0) #0 {
  %2 = alloca i32, align 4
  %3 = alloca %struct.Node*, align 8
  store i32 %0, i32* %2, align 4
  %4 = call noalias i8* @malloc(i64 noundef 24) #4
  %5 = bitcast i8* %4 to %struct.Node*
  store %struct.Node* %5, %struct.Node** %3, align 8
  %6 = load %struct.Node*, %struct.Node** %3, align 8
  %7 = icmp eq %struct.Node* %6, null
  br i1 %7, label %8, label %10

8:                                                ; preds = %1
  %9 = call i32 (i8*, ...) @printf(i8* noundef getelementptr inbounds ([26 x i8], [26 x i8]* @.str, i64 0, i64 0))
  call void @exit(i32 noundef 1) #5
  unreachable

10:                                               ; preds = %1
  %11 = load i32, i32* %2, align 4
  %12 = load %struct.Node*, %struct.Node** %3, align 8
  %13 = getelementptr inbounds %struct.Node, %struct.Node* %12, i32 0, i32 0
  store i32 %11, i32* %13, align 8
  %14 = load %struct.Node*, %struct.Node** %3, align 8
  %15 = getelementptr inbounds %struct.Node, %struct.Node* %14, i32 0, i32 1
  store %struct.Node* null, %struct.Node** %15, align 8
  %16 = load %struct.Node*, %struct.Node** %3, align 8
  %17 = getelementptr inbounds %struct.Node, %struct.Node* %16, i32 0, i32 2
  store %struct.Node* null, %struct.Node** %17, align 8
  %18 = load %struct.Node*, %struct.Node** %3, align 8
  ret %struct.Node* %18
}

; Function Attrs: nounwind
declare noalias i8* @malloc(i64 noundef) #1

declare i32 @printf(i8* noundef, ...) #2

; Function Attrs: noreturn nounwind
declare void @exit(i32 noundef) #3

; Function Attrs: noinline nounwind optnone uwtable
define dso_local %struct.Node* @insert(%struct.Node* noundef %0, i32 noundef %1) #0 {
  %3 = alloca %struct.Node*, align 8
  %4 = alloca %struct.Node*, align 8
  %5 = alloca i32, align 4
  store %struct.Node* %0, %struct.Node** %4, align 8
  store i32 %1, i32* %5, align 4
  %6 = load %struct.Node*, %struct.Node** %4, align 8
  %7 = icmp eq %struct.Node* %6, null
  br i1 %7, label %8, label %11

8:                                                ; preds = %2
  %9 = load i32, i32* %5, align 4
  %10 = call %struct.Node* @createNode(i32 noundef %9)
  store %struct.Node* %10, %struct.Node** %3, align 8
  br label %42

11:                                               ; preds = %2
  %12 = load i32, i32* %5, align 4
  %13 = load %struct.Node*, %struct.Node** %4, align 8
  %14 = getelementptr inbounds %struct.Node, %struct.Node* %13, i32 0, i32 0
  %15 = load i32, i32* %14, align 8
  %16 = icmp slt i32 %12, %15
  br i1 %16, label %17, label %25

17:                                               ; preds = %11
  %18 = load %struct.Node*, %struct.Node** %4, align 8
  %19 = getelementptr inbounds %struct.Node, %struct.Node* %18, i32 0, i32 1
  %20 = load %struct.Node*, %struct.Node** %19, align 8
  %21 = load i32, i32* %5, align 4
  %22 = call %struct.Node* @insert(%struct.Node* noundef %20, i32 noundef %21)
  %23 = load %struct.Node*, %struct.Node** %4, align 8
  %24 = getelementptr inbounds %struct.Node, %struct.Node* %23, i32 0, i32 1
  store %struct.Node* %22, %struct.Node** %24, align 8
  br label %40

25:                                               ; preds = %11
  %26 = load i32, i32* %5, align 4
  %27 = load %struct.Node*, %struct.Node** %4, align 8
  %28 = getelementptr inbounds %struct.Node, %struct.Node* %27, i32 0, i32 0
  %29 = load i32, i32* %28, align 8
  %30 = icmp sgt i32 %26, %29
  br i1 %30, label %31, label %39

31:                                               ; preds = %25
  %32 = load %struct.Node*, %struct.Node** %4, align 8
  %33 = getelementptr inbounds %struct.Node, %struct.Node* %32, i32 0, i32 2
  %34 = load %struct.Node*, %struct.Node** %33, align 8
  %35 = load i32, i32* %5, align 4
  %36 = call %struct.Node* @insert(%struct.Node* noundef %34, i32 noundef %35)
  %37 = load %struct.Node*, %struct.Node** %4, align 8
  %38 = getelementptr inbounds %struct.Node, %struct.Node* %37, i32 0, i32 2
  store %struct.Node* %36, %struct.Node** %38, align 8
  br label %39

39:                                               ; preds = %31, %25
  br label %40

40:                                               ; preds = %39, %17
  %41 = load %struct.Node*, %struct.Node** %4, align 8
  store %struct.Node* %41, %struct.Node** %3, align 8
  br label %42

42:                                               ; preds = %40, %8
  %43 = load %struct.Node*, %struct.Node** %3, align 8
  ret %struct.Node* %43
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local %struct.Node* @findMin(%struct.Node* noundef %0) #0 {
  %2 = alloca %struct.Node*, align 8
  %3 = alloca %struct.Node*, align 8
  store %struct.Node* %0, %struct.Node** %3, align 8
  %4 = load %struct.Node*, %struct.Node** %3, align 8
  %5 = icmp eq %struct.Node* %4, null
  br i1 %5, label %6, label %7

6:                                                ; preds = %1
  store %struct.Node* null, %struct.Node** %2, align 8
  br label %19

7:                                                ; preds = %1
  br label %8

8:                                                ; preds = %13, %7
  %9 = load %struct.Node*, %struct.Node** %3, align 8
  %10 = getelementptr inbounds %struct.Node, %struct.Node* %9, i32 0, i32 1
  %11 = load %struct.Node*, %struct.Node** %10, align 8
  %12 = icmp ne %struct.Node* %11, null
  br i1 %12, label %13, label %17

13:                                               ; preds = %8
  %14 = load %struct.Node*, %struct.Node** %3, align 8
  %15 = getelementptr inbounds %struct.Node, %struct.Node* %14, i32 0, i32 1
  %16 = load %struct.Node*, %struct.Node** %15, align 8
  store %struct.Node* %16, %struct.Node** %3, align 8
  br label %8, !llvm.loop !6

17:                                               ; preds = %8
  %18 = load %struct.Node*, %struct.Node** %3, align 8
  store %struct.Node* %18, %struct.Node** %2, align 8
  br label %19

19:                                               ; preds = %17, %6
  %20 = load %struct.Node*, %struct.Node** %2, align 8
  ret %struct.Node* %20
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local %struct.Node* @deleteNode(%struct.Node* noundef %0, i32 noundef %1) #0 {
  %3 = alloca %struct.Node*, align 8
  %4 = alloca %struct.Node*, align 8
  %5 = alloca i32, align 4
  %6 = alloca %struct.Node*, align 8
  %7 = alloca %struct.Node*, align 8
  %8 = alloca %struct.Node*, align 8
  store %struct.Node* %0, %struct.Node** %4, align 8
  store i32 %1, i32* %5, align 4
  %9 = load %struct.Node*, %struct.Node** %4, align 8
  %10 = icmp eq %struct.Node* %9, null
  br i1 %10, label %11, label %13

11:                                               ; preds = %2
  %12 = load %struct.Node*, %struct.Node** %4, align 8
  store %struct.Node* %12, %struct.Node** %3, align 8
  br label %88

13:                                               ; preds = %2
  %14 = load i32, i32* %5, align 4
  %15 = load %struct.Node*, %struct.Node** %4, align 8
  %16 = getelementptr inbounds %struct.Node, %struct.Node* %15, i32 0, i32 0
  %17 = load i32, i32* %16, align 8
  %18 = icmp slt i32 %14, %17
  br i1 %18, label %19, label %27

19:                                               ; preds = %13
  %20 = load %struct.Node*, %struct.Node** %4, align 8
  %21 = getelementptr inbounds %struct.Node, %struct.Node* %20, i32 0, i32 1
  %22 = load %struct.Node*, %struct.Node** %21, align 8
  %23 = load i32, i32* %5, align 4
  %24 = call %struct.Node* @deleteNode(%struct.Node* noundef %22, i32 noundef %23)
  %25 = load %struct.Node*, %struct.Node** %4, align 8
  %26 = getelementptr inbounds %struct.Node, %struct.Node* %25, i32 0, i32 1
  store %struct.Node* %24, %struct.Node** %26, align 8
  br label %86

27:                                               ; preds = %13
  %28 = load i32, i32* %5, align 4
  %29 = load %struct.Node*, %struct.Node** %4, align 8
  %30 = getelementptr inbounds %struct.Node, %struct.Node* %29, i32 0, i32 0
  %31 = load i32, i32* %30, align 8
  %32 = icmp sgt i32 %28, %31
  br i1 %32, label %33, label %41

33:                                               ; preds = %27
  %34 = load %struct.Node*, %struct.Node** %4, align 8
  %35 = getelementptr inbounds %struct.Node, %struct.Node* %34, i32 0, i32 2
  %36 = load %struct.Node*, %struct.Node** %35, align 8
  %37 = load i32, i32* %5, align 4
  %38 = call %struct.Node* @deleteNode(%struct.Node* noundef %36, i32 noundef %37)
  %39 = load %struct.Node*, %struct.Node** %4, align 8
  %40 = getelementptr inbounds %struct.Node, %struct.Node* %39, i32 0, i32 2
  store %struct.Node* %38, %struct.Node** %40, align 8
  br label %85

41:                                               ; preds = %27
  %42 = load %struct.Node*, %struct.Node** %4, align 8
  %43 = getelementptr inbounds %struct.Node, %struct.Node* %42, i32 0, i32 1
  %44 = load %struct.Node*, %struct.Node** %43, align 8
  %45 = icmp eq %struct.Node* %44, null
  br i1 %45, label %46, label %53

46:                                               ; preds = %41
  %47 = load %struct.Node*, %struct.Node** %4, align 8
  %48 = getelementptr inbounds %struct.Node, %struct.Node* %47, i32 0, i32 2
  %49 = load %struct.Node*, %struct.Node** %48, align 8
  store %struct.Node* %49, %struct.Node** %6, align 8
  %50 = load %struct.Node*, %struct.Node** %4, align 8
  %51 = bitcast %struct.Node* %50 to i8*
  call void @free(i8* noundef %51) #4
  %52 = load %struct.Node*, %struct.Node** %6, align 8
  store %struct.Node* %52, %struct.Node** %3, align 8
  br label %88

53:                                               ; preds = %41
  %54 = load %struct.Node*, %struct.Node** %4, align 8
  %55 = getelementptr inbounds %struct.Node, %struct.Node* %54, i32 0, i32 2
  %56 = load %struct.Node*, %struct.Node** %55, align 8
  %57 = icmp eq %struct.Node* %56, null
  br i1 %57, label %58, label %65

58:                                               ; preds = %53
  %59 = load %struct.Node*, %struct.Node** %4, align 8
  %60 = getelementptr inbounds %struct.Node, %struct.Node* %59, i32 0, i32 1
  %61 = load %struct.Node*, %struct.Node** %60, align 8
  store %struct.Node* %61, %struct.Node** %7, align 8
  %62 = load %struct.Node*, %struct.Node** %4, align 8
  %63 = bitcast %struct.Node* %62 to i8*
  call void @free(i8* noundef %63) #4
  %64 = load %struct.Node*, %struct.Node** %7, align 8
  store %struct.Node* %64, %struct.Node** %3, align 8
  br label %88

65:                                               ; preds = %53
  br label %66

66:                                               ; preds = %65
  %67 = load %struct.Node*, %struct.Node** %4, align 8
  %68 = getelementptr inbounds %struct.Node, %struct.Node* %67, i32 0, i32 2
  %69 = load %struct.Node*, %struct.Node** %68, align 8
  %70 = call %struct.Node* @findMin(%struct.Node* noundef %69)
  store %struct.Node* %70, %struct.Node** %8, align 8
  %71 = load %struct.Node*, %struct.Node** %8, align 8
  %72 = getelementptr inbounds %struct.Node, %struct.Node* %71, i32 0, i32 0
  %73 = load i32, i32* %72, align 8
  %74 = load %struct.Node*, %struct.Node** %4, align 8
  %75 = getelementptr inbounds %struct.Node, %struct.Node* %74, i32 0, i32 0
  store i32 %73, i32* %75, align 8
  %76 = load %struct.Node*, %struct.Node** %4, align 8
  %77 = getelementptr inbounds %struct.Node, %struct.Node* %76, i32 0, i32 2
  %78 = load %struct.Node*, %struct.Node** %77, align 8
  %79 = load %struct.Node*, %struct.Node** %8, align 8
  %80 = getelementptr inbounds %struct.Node, %struct.Node* %79, i32 0, i32 0
  %81 = load i32, i32* %80, align 8
  %82 = call %struct.Node* @deleteNode(%struct.Node* noundef %78, i32 noundef %81)
  %83 = load %struct.Node*, %struct.Node** %4, align 8
  %84 = getelementptr inbounds %struct.Node, %struct.Node* %83, i32 0, i32 2
  store %struct.Node* %82, %struct.Node** %84, align 8
  br label %85

85:                                               ; preds = %66, %33
  br label %86

86:                                               ; preds = %85, %19
  %87 = load %struct.Node*, %struct.Node** %4, align 8
  store %struct.Node* %87, %struct.Node** %3, align 8
  br label %88

88:                                               ; preds = %86, %58, %46, %11
  %89 = load %struct.Node*, %struct.Node** %3, align 8
  ret %struct.Node* %89
}

; Function Attrs: nounwind
declare void @free(i8* noundef) #1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @inOrderTraversal(%struct.Node* noundef %0) #0 {
  %2 = alloca %struct.Node*, align 8
  store %struct.Node* %0, %struct.Node** %2, align 8
  %3 = load %struct.Node*, %struct.Node** %2, align 8
  %4 = icmp ne %struct.Node* %3, null
  br i1 %4, label %5, label %16

5:                                                ; preds = %1
  %6 = load %struct.Node*, %struct.Node** %2, align 8
  %7 = getelementptr inbounds %struct.Node, %struct.Node* %6, i32 0, i32 1
  %8 = load %struct.Node*, %struct.Node** %7, align 8
  call void @inOrderTraversal(%struct.Node* noundef %8)
  %9 = load %struct.Node*, %struct.Node** %2, align 8
  %10 = getelementptr inbounds %struct.Node, %struct.Node* %9, i32 0, i32 0
  %11 = load i32, i32* %10, align 8
  %12 = call i32 (i8*, ...) @printf(i8* noundef getelementptr inbounds ([4 x i8], [4 x i8]* @.str.1, i64 0, i64 0), i32 noundef %11)
  %13 = load %struct.Node*, %struct.Node** %2, align 8
  %14 = getelementptr inbounds %struct.Node, %struct.Node* %13, i32 0, i32 2
  %15 = load %struct.Node*, %struct.Node** %14, align 8
  call void @inOrderTraversal(%struct.Node* noundef %15)
  br label %16

16:                                               ; preds = %5, %1
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local zeroext i1 @search(%struct.Node* noundef %0, i32 noundef %1) #0 {
  %3 = alloca i1, align 1
  %4 = alloca %struct.Node*, align 8
  %5 = alloca i32, align 4
  store %struct.Node* %0, %struct.Node** %4, align 8
  store i32 %1, i32* %5, align 4
  %6 = load %struct.Node*, %struct.Node** %4, align 8
  %7 = icmp eq %struct.Node* %6, null
  br i1 %7, label %8, label %9

8:                                                ; preds = %2
  store i1 false, i1* %3, align 1
  br label %34

9:                                                ; preds = %2
  %10 = load %struct.Node*, %struct.Node** %4, align 8
  %11 = getelementptr inbounds %struct.Node, %struct.Node* %10, i32 0, i32 0
  %12 = load i32, i32* %11, align 8
  %13 = load i32, i32* %5, align 4
  %14 = icmp eq i32 %12, %13
  br i1 %14, label %15, label %16

15:                                               ; preds = %9
  store i1 true, i1* %3, align 1
  br label %34

16:                                               ; preds = %9
  %17 = load i32, i32* %5, align 4
  %18 = load %struct.Node*, %struct.Node** %4, align 8
  %19 = getelementptr inbounds %struct.Node, %struct.Node* %18, i32 0, i32 0
  %20 = load i32, i32* %19, align 8
  %21 = icmp slt i32 %17, %20
  br i1 %21, label %22, label %28

22:                                               ; preds = %16
  %23 = load %struct.Node*, %struct.Node** %4, align 8
  %24 = getelementptr inbounds %struct.Node, %struct.Node* %23, i32 0, i32 1
  %25 = load %struct.Node*, %struct.Node** %24, align 8
  %26 = load i32, i32* %5, align 4
  %27 = call zeroext i1 @search(%struct.Node* noundef %25, i32 noundef %26)
  store i1 %27, i1* %3, align 1
  br label %34

28:                                               ; preds = %16
  %29 = load %struct.Node*, %struct.Node** %4, align 8
  %30 = getelementptr inbounds %struct.Node, %struct.Node* %29, i32 0, i32 2
  %31 = load %struct.Node*, %struct.Node** %30, align 8
  %32 = load i32, i32* %5, align 4
  %33 = call zeroext i1 @search(%struct.Node* noundef %31, i32 noundef %32)
  store i1 %33, i1* %3, align 1
  br label %34

34:                                               ; preds = %28, %22, %15, %8
  %35 = load i1, i1* %3, align 1
  ret i1 %35
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @freeTree(%struct.Node* noundef %0) #0 {
  %2 = alloca %struct.Node*, align 8
  store %struct.Node* %0, %struct.Node** %2, align 8
  %3 = load %struct.Node*, %struct.Node** %2, align 8
  %4 = icmp ne %struct.Node* %3, null
  br i1 %4, label %5, label %14

5:                                                ; preds = %1
  %6 = load %struct.Node*, %struct.Node** %2, align 8
  %7 = getelementptr inbounds %struct.Node, %struct.Node* %6, i32 0, i32 1
  %8 = load %struct.Node*, %struct.Node** %7, align 8
  call void @freeTree(%struct.Node* noundef %8)
  %9 = load %struct.Node*, %struct.Node** %2, align 8
  %10 = getelementptr inbounds %struct.Node, %struct.Node* %9, i32 0, i32 2
  %11 = load %struct.Node*, %struct.Node** %10, align 8
  call void @freeTree(%struct.Node* noundef %11)
  %12 = load %struct.Node*, %struct.Node** %2, align 8
  %13 = bitcast %struct.Node* %12 to i8*
  call void @free(i8* noundef %13) #4
  br label %14

14:                                               ; preds = %5, %1
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main() #0 {
  %1 = alloca i32, align 4
  %2 = alloca %struct.Node*, align 8
  store i32 0, i32* %1, align 4
  store %struct.Node* null, %struct.Node** %2, align 8
  %3 = load %struct.Node*, %struct.Node** %2, align 8
  %4 = call %struct.Node* @insert(%struct.Node* noundef %3, i32 noundef 50)
  store %struct.Node* %4, %struct.Node** %2, align 8
  %5 = load %struct.Node*, %struct.Node** %2, align 8
  %6 = call %struct.Node* @insert(%struct.Node* noundef %5, i32 noundef 30)
  %7 = load %struct.Node*, %struct.Node** %2, align 8
  %8 = call %struct.Node* @insert(%struct.Node* noundef %7, i32 noundef 20)
  %9 = load %struct.Node*, %struct.Node** %2, align 8
  %10 = call %struct.Node* @insert(%struct.Node* noundef %9, i32 noundef 40)
  %11 = load %struct.Node*, %struct.Node** %2, align 8
  %12 = call %struct.Node* @insert(%struct.Node* noundef %11, i32 noundef 70)
  %13 = load %struct.Node*, %struct.Node** %2, align 8
  %14 = call %struct.Node* @insert(%struct.Node* noundef %13, i32 noundef 60)
  %15 = load %struct.Node*, %struct.Node** %2, align 8
  %16 = call %struct.Node* @insert(%struct.Node* noundef %15, i32 noundef 80)
  %17 = call i32 (i8*, ...) @printf(i8* noundef getelementptr inbounds ([21 x i8], [21 x i8]* @.str.2, i64 0, i64 0))
  %18 = load %struct.Node*, %struct.Node** %2, align 8
  call void @inOrderTraversal(%struct.Node* noundef %18)
  %19 = call i32 (i8*, ...) @printf(i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.3, i64 0, i64 0))
  %20 = call i32 (i8*, ...) @printf(i8* noundef getelementptr inbounds ([13 x i8], [13 x i8]* @.str.4, i64 0, i64 0))
  %21 = load %struct.Node*, %struct.Node** %2, align 8
  %22 = call %struct.Node* @deleteNode(%struct.Node* noundef %21, i32 noundef 20)
  store %struct.Node* %22, %struct.Node** %2, align 8
  %23 = call i32 (i8*, ...) @printf(i8* noundef getelementptr inbounds ([21 x i8], [21 x i8]* @.str.2, i64 0, i64 0))
  %24 = load %struct.Node*, %struct.Node** %2, align 8
  call void @inOrderTraversal(%struct.Node* noundef %24)
  %25 = call i32 (i8*, ...) @printf(i8* noundef getelementptr inbounds ([2 x i8], [2 x i8]* @.str.3, i64 0, i64 0))
  %26 = load %struct.Node*, %struct.Node** %2, align 8
  %27 = call zeroext i1 @search(%struct.Node* noundef %26, i32 noundef 40)
  %28 = zext i1 %27 to i64
  %29 = select i1 %27, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.6, i64 0, i64 0), i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.7, i64 0, i64 0)
  %30 = call i32 (i8*, ...) @printf(i8* noundef getelementptr inbounds ([22 x i8], [22 x i8]* @.str.5, i64 0, i64 0), i8* noundef %29)
  %31 = load %struct.Node*, %struct.Node** %2, align 8
  %32 = call zeroext i1 @search(%struct.Node* noundef %31, i32 noundef 100)
  %33 = zext i1 %32 to i64
  %34 = select i1 %32, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.6, i64 0, i64 0), i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.7, i64 0, i64 0)
  %35 = call i32 (i8*, ...) @printf(i8* noundef getelementptr inbounds ([23 x i8], [23 x i8]* @.str.8, i64 0, i64 0), i8* noundef %34)
  %36 = load %struct.Node*, %struct.Node** %2, align 8
  call void @freeTree(%struct.Node* noundef %36)
  ret i32 0
}

attributes #0 = { noinline nounwind optnone uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { nounwind "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #2 = { "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #3 = { noreturn nounwind "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #4 = { nounwind }
attributes #5 = { noreturn nounwind }

!llvm.module.flags = !{!0, !1, !2, !3, !4}
!llvm.ident = !{!5}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 7, !"PIC Level", i32 2}
!2 = !{i32 7, !"PIE Level", i32 2}
!3 = !{i32 7, !"uwtable", i32 1}
!4 = !{i32 7, !"frame-pointer", i32 2}
!5 = !{!"Ubuntu clang version 14.0.0-1ubuntu1.1"}
!6 = distinct !{!6, !7}
!7 = !{!"llvm.loop.mustprogress"}
