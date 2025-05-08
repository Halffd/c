; ModuleID = 'factorial.c'
source_filename = "factorial.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@memo = dso_local local_unnamed_addr global ptr null, align 8
@.str = private unnamed_addr constant [23 x i8] c"Tail factorial %d: %d\0A\00", align 1
@.str.1 = private unnamed_addr constant [17 x i8] c"Fibonaci %d: %d\0A\00", align 1
@.str.7 = private unnamed_addr constant [26 x i8] c"Enter your choice (1-4): \00", align 1
@.str.8 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@.str.9 = private unnamed_addr constant [17 x i8] c"Enter a number: \00", align 1
@.str.10 = private unnamed_addr constant [34 x i8] c"\0AFactorial of %d (iterative): %d\0A\00", align 1
@.str.11 = private unnamed_addr constant [34 x i8] c"\0AFactorial of %d (recursive): %d\0A\00", align 1
@.str.12 = private unnamed_addr constant [49 x i8] c"\0AFibonacci sequence (iterative) up to %d terms:\0A\00", align 1
@.str.13 = private unnamed_addr constant [4 x i8] c"%d \00", align 1
@.str.15 = private unnamed_addr constant [49 x i8] c"\0AFibonacci sequence (recursive) up to %d terms:\0A\00", align 1
@str = private unnamed_addr constant [33 x i8] c"\0A=== ALGORITHM DEMONSTRATION ===\00", align 1
@str.17 = private unnamed_addr constant [25 x i8] c"1. Factorial (Iterative)\00", align 1
@str.18 = private unnamed_addr constant [25 x i8] c"2. Factorial (Recursive)\00", align 1
@str.19 = private unnamed_addr constant [25 x i8] c"3. Fibonacci (Iterative)\00", align 1
@str.20 = private unnamed_addr constant [25 x i8] c"4. Fibonacci (Recursive)\00", align 1
@str.21 = private unnamed_addr constant [17 x i8] c"\0AInvalid choice!\00", align 1

; Function Attrs: nofree nosync nounwind sspstrong memory(readwrite, inaccessiblemem: none) uwtable
define dso_local i32 @fibonacci_memo(i32 noundef %0) local_unnamed_addr #0 {
  %2 = load ptr, ptr @memo, align 8, !tbaa !7
  %3 = sext i32 %0 to i64
  %4 = getelementptr inbounds i32, ptr %2, i64 %3
  %5 = load i32, ptr %4, align 4, !tbaa !11
  %6 = icmp eq i32 %5, -1
  br i1 %6, label %7, label %10

7:                                                ; preds = %1
  %8 = icmp slt i32 %0, 2
  br i1 %8, label %9, label %12

9:                                                ; preds = %7
  store i32 %0, ptr %4, align 4, !tbaa !11
  br label %10

10:                                               ; preds = %1, %9, %12
  %11 = phi i32 [ %17, %12 ], [ %0, %9 ], [ %5, %1 ]
  ret i32 %11

12:                                               ; preds = %7
  %13 = add nsw i32 %0, -1
  %14 = tail call i32 @fibonacci_memo(i32 noundef %13)
  %15 = add nsw i32 %0, -2
  %16 = tail call i32 @fibonacci_memo(i32 noundef %15)
  %17 = add nsw i32 %16, %14
  %18 = load ptr, ptr @memo, align 8, !tbaa !7
  %19 = getelementptr inbounds i32, ptr %18, i64 %3
  store i32 %17, ptr %19, align 4, !tbaa !11
  br label %10
}

; Function Attrs: nounwind sspstrong uwtable
define dso_local i32 @fibonacci(i32 noundef %0) local_unnamed_addr #1 {
  %2 = add i32 %0, 1
  %3 = sext i32 %2 to i64
  %4 = shl nsw i64 %3, 2
  %5 = tail call noalias ptr @malloc(i64 noundef %4) #11
  store ptr %5, ptr @memo, align 8, !tbaa !7
  %6 = icmp slt i32 %0, 0
  br i1 %6, label %10, label %7

7:                                                ; preds = %1
  %8 = zext i32 %2 to i64
  %9 = shl nuw nsw i64 %8, 2
  tail call void @llvm.memset.p0.i64(ptr align 4 %5, i8 -1, i64 %9, i1 false), !tbaa !11
  br label %10

10:                                               ; preds = %7, %1
  %11 = tail call i32 @fibonacci_memo(i32 noundef %0)
  %12 = load ptr, ptr @memo, align 8, !tbaa !7
  tail call void @free(ptr noundef %12) #12
  ret i32 %11
}

; Function Attrs: mustprogress nofree nounwind willreturn allockind("alloc,uninitialized") allocsize(0) memory(inaccessiblemem: readwrite)
declare noalias noundef ptr @malloc(i64 noundef) local_unnamed_addr #2

; Function Attrs: mustprogress nocallback nofree nosync nounwind willreturn memory(argmem: readwrite)
declare void @llvm.lifetime.start.p0(i64 immarg, ptr nocapture) #3

; Function Attrs: mustprogress nocallback nofree nosync nounwind willreturn memory(argmem: readwrite)
declare void @llvm.lifetime.end.p0(i64 immarg, ptr nocapture) #3

; Function Attrs: mustprogress nounwind willreturn allockind("free") memory(argmem: readwrite, inaccessiblemem: readwrite)
declare void @free(ptr allocptr nocapture noundef) local_unnamed_addr #4

; Function Attrs: nofree norecurse nosync nounwind sspstrong memory(none) uwtable
define dso_local i32 @factorial_tail(i32 noundef %0, i32 noundef %1) local_unnamed_addr #5 {
  %3 = icmp slt i32 %0, 2
  br i1 %3, label %46, label %4

4:                                                ; preds = %2
  %5 = add nsw i32 %0, -1
  %6 = icmp ult i32 %0, 33
  br i1 %6, label %37, label %7

7:                                                ; preds = %4
  %8 = and i32 %5, -32
  %9 = sub i32 %0, %8
  %10 = insertelement <8 x i32> <i32 poison, i32 1, i32 1, i32 1, i32 1, i32 1, i32 1, i32 1>, i32 %1, i64 0
  %11 = insertelement <8 x i32> poison, i32 %0, i64 0
  %12 = shufflevector <8 x i32> %11, <8 x i32> poison, <8 x i32> zeroinitializer
  %13 = add nsw <8 x i32> %12, <i32 0, i32 -1, i32 -2, i32 -3, i32 -4, i32 -5, i32 -6, i32 -7>
  br label %14

14:                                               ; preds = %14, %7
  %15 = phi i32 [ 0, %7 ], [ %28, %14 ]
  %16 = phi <8 x i32> [ %10, %7 ], [ %24, %14 ]
  %17 = phi <8 x i32> [ <i32 1, i32 1, i32 1, i32 1, i32 1, i32 1, i32 1, i32 1>, %7 ], [ %25, %14 ]
  %18 = phi <8 x i32> [ <i32 1, i32 1, i32 1, i32 1, i32 1, i32 1, i32 1, i32 1>, %7 ], [ %26, %14 ]
  %19 = phi <8 x i32> [ <i32 1, i32 1, i32 1, i32 1, i32 1, i32 1, i32 1, i32 1>, %7 ], [ %27, %14 ]
  %20 = phi <8 x i32> [ %13, %7 ], [ %29, %14 ]
  %21 = add <8 x i32> %20, <i32 -8, i32 -8, i32 -8, i32 -8, i32 -8, i32 -8, i32 -8, i32 -8>
  %22 = add <8 x i32> %20, <i32 -16, i32 -16, i32 -16, i32 -16, i32 -16, i32 -16, i32 -16, i32 -16>
  %23 = add <8 x i32> %20, <i32 -24, i32 -24, i32 -24, i32 -24, i32 -24, i32 -24, i32 -24, i32 -24>
  %24 = mul <8 x i32> %16, %20
  %25 = mul <8 x i32> %17, %21
  %26 = mul <8 x i32> %18, %22
  %27 = mul <8 x i32> %19, %23
  %28 = add nuw i32 %15, 32
  %29 = add <8 x i32> %20, <i32 -32, i32 -32, i32 -32, i32 -32, i32 -32, i32 -32, i32 -32, i32 -32>
  %30 = icmp eq i32 %28, %8
  br i1 %30, label %31, label %14, !llvm.loop !13

31:                                               ; preds = %14
  %32 = mul <8 x i32> %25, %24
  %33 = mul <8 x i32> %26, %32
  %34 = mul <8 x i32> %27, %33
  %35 = tail call i32 @llvm.vector.reduce.mul.v8i32(<8 x i32> %34)
  %36 = icmp eq i32 %5, %8
  br i1 %36, label %46, label %37

37:                                               ; preds = %31, %4
  %38 = phi i32 [ %1, %4 ], [ %35, %31 ]
  %39 = phi i32 [ %0, %4 ], [ %9, %31 ]
  br label %40

40:                                               ; preds = %37, %40
  %41 = phi i32 [ %44, %40 ], [ %38, %37 ]
  %42 = phi i32 [ %43, %40 ], [ %39, %37 ]
  %43 = add nsw i32 %42, -1
  %44 = mul nsw i32 %41, %42
  %45 = icmp ult i32 %42, 3
  br i1 %45, label %46, label %40, !llvm.loop !16

46:                                               ; preds = %40, %31, %2
  %47 = phi i32 [ %1, %2 ], [ %35, %31 ], [ %44, %40 ]
  ret i32 %47
}

; Function Attrs: nofree norecurse nosync nounwind sspstrong memory(none) uwtable
define dso_local i32 @factorial_optimized(i32 noundef %0) local_unnamed_addr #5 {
  %2 = icmp slt i32 %0, 2
  br i1 %2, label %44, label %3

3:                                                ; preds = %1
  %4 = add nsw i32 %0, -1
  %5 = icmp ult i32 %0, 33
  br i1 %5, label %35, label %6

6:                                                ; preds = %3
  %7 = and i32 %4, -32
  %8 = sub i32 %0, %7
  %9 = insertelement <8 x i32> poison, i32 %0, i64 0
  %10 = shufflevector <8 x i32> %9, <8 x i32> poison, <8 x i32> zeroinitializer
  %11 = add nsw <8 x i32> %10, <i32 0, i32 -1, i32 -2, i32 -3, i32 -4, i32 -5, i32 -6, i32 -7>
  br label %12

12:                                               ; preds = %12, %6
  %13 = phi i32 [ 0, %6 ], [ %26, %12 ]
  %14 = phi <8 x i32> [ <i32 1, i32 1, i32 1, i32 1, i32 1, i32 1, i32 1, i32 1>, %6 ], [ %22, %12 ]
  %15 = phi <8 x i32> [ <i32 1, i32 1, i32 1, i32 1, i32 1, i32 1, i32 1, i32 1>, %6 ], [ %23, %12 ]
  %16 = phi <8 x i32> [ <i32 1, i32 1, i32 1, i32 1, i32 1, i32 1, i32 1, i32 1>, %6 ], [ %24, %12 ]
  %17 = phi <8 x i32> [ <i32 1, i32 1, i32 1, i32 1, i32 1, i32 1, i32 1, i32 1>, %6 ], [ %25, %12 ]
  %18 = phi <8 x i32> [ %11, %6 ], [ %27, %12 ]
  %19 = add <8 x i32> %18, <i32 -8, i32 -8, i32 -8, i32 -8, i32 -8, i32 -8, i32 -8, i32 -8>
  %20 = add <8 x i32> %18, <i32 -16, i32 -16, i32 -16, i32 -16, i32 -16, i32 -16, i32 -16, i32 -16>
  %21 = add <8 x i32> %18, <i32 -24, i32 -24, i32 -24, i32 -24, i32 -24, i32 -24, i32 -24, i32 -24>
  %22 = mul <8 x i32> %18, %14
  %23 = mul <8 x i32> %19, %15
  %24 = mul <8 x i32> %20, %16
  %25 = mul <8 x i32> %21, %17
  %26 = add nuw i32 %13, 32
  %27 = add <8 x i32> %18, <i32 -32, i32 -32, i32 -32, i32 -32, i32 -32, i32 -32, i32 -32, i32 -32>
  %28 = icmp eq i32 %26, %7
  br i1 %28, label %29, label %12, !llvm.loop !17

29:                                               ; preds = %12
  %30 = mul <8 x i32> %23, %22
  %31 = mul <8 x i32> %24, %30
  %32 = mul <8 x i32> %25, %31
  %33 = tail call i32 @llvm.vector.reduce.mul.v8i32(<8 x i32> %32)
  %34 = icmp eq i32 %4, %7
  br i1 %34, label %44, label %35

35:                                               ; preds = %29, %3
  %36 = phi i32 [ 1, %3 ], [ %33, %29 ]
  %37 = phi i32 [ %0, %3 ], [ %8, %29 ]
  br label %38

38:                                               ; preds = %35, %38
  %39 = phi i32 [ %42, %38 ], [ %36, %35 ]
  %40 = phi i32 [ %41, %38 ], [ %37, %35 ]
  %41 = add nsw i32 %40, -1
  %42 = mul nsw i32 %40, %39
  %43 = icmp ult i32 %40, 3
  br i1 %43, label %44, label %38, !llvm.loop !18

44:                                               ; preds = %38, %29, %1
  %45 = phi i32 [ 1, %1 ], [ %33, %29 ], [ %42, %38 ]
  ret i32 %45
}

; Function Attrs: nounwind sspstrong uwtable
define dso_local noundef i32 @main() local_unnamed_addr #1 {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  call void @llvm.lifetime.start.p0(i64 4, ptr nonnull %1) #12
  call void @llvm.lifetime.start.p0(i64 4, ptr nonnull %2) #12
  %3 = tail call noalias dereferenceable_or_null(124) ptr @malloc(i64 noundef 124) #11
  store ptr %3, ptr @memo, align 8, !tbaa !7
  tail call void @llvm.memset.p0.i64(ptr noundef nonnull align 4 dereferenceable(124) %3, i8 -1, i64 124, i1 false), !tbaa !11
  %4 = tail call i32 @fibonacci_memo(i32 noundef 30)
  %5 = load ptr, ptr @memo, align 8, !tbaa !7
  tail call void @free(ptr noundef %5) #12
  %6 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str, i32 noundef 30, i32 noundef 1409286144)
  %7 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.1, i32 noundef 30, i32 noundef %4)
  %8 = tail call i32 @puts(ptr nonnull dereferenceable(1) @str)
  %9 = tail call i32 @puts(ptr nonnull dereferenceable(1) @str.17)
  %10 = tail call i32 @puts(ptr nonnull dereferenceable(1) @str.18)
  %11 = tail call i32 @puts(ptr nonnull dereferenceable(1) @str.19)
  %12 = tail call i32 @puts(ptr nonnull dereferenceable(1) @str.20)
  %13 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.7)
  %14 = call i32 (ptr, ...) @__isoc99_scanf(ptr noundef nonnull @.str.8, ptr noundef nonnull %1)
  %15 = call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.9)
  %16 = call i32 (ptr, ...) @__isoc99_scanf(ptr noundef nonnull @.str.8, ptr noundef nonnull %2)
  %17 = load i32, ptr %1, align 4, !tbaa !11
  switch i32 %17, label %176 [
    i32 1, label %18
    i32 2, label %65
    i32 3, label %112
    i32 4, label %162
  ]

18:                                               ; preds = %0
  %19 = load i32, ptr %2, align 4, !tbaa !11
  %20 = icmp sgt i32 %19, 1
  br i1 %20, label %21, label %62

21:                                               ; preds = %18
  %22 = add nsw i32 %19, -1
  %23 = icmp ult i32 %19, 33
  br i1 %23, label %53, label %24

24:                                               ; preds = %21
  %25 = and i32 %22, -32
  %26 = sub i32 %19, %25
  %27 = insertelement <8 x i32> poison, i32 %19, i64 0
  %28 = shufflevector <8 x i32> %27, <8 x i32> poison, <8 x i32> zeroinitializer
  %29 = add nsw <8 x i32> %28, <i32 0, i32 -1, i32 -2, i32 -3, i32 -4, i32 -5, i32 -6, i32 -7>
  br label %30

30:                                               ; preds = %30, %24
  %31 = phi i32 [ 0, %24 ], [ %44, %30 ]
  %32 = phi <8 x i32> [ <i32 1, i32 1, i32 1, i32 1, i32 1, i32 1, i32 1, i32 1>, %24 ], [ %40, %30 ]
  %33 = phi <8 x i32> [ <i32 1, i32 1, i32 1, i32 1, i32 1, i32 1, i32 1, i32 1>, %24 ], [ %41, %30 ]
  %34 = phi <8 x i32> [ <i32 1, i32 1, i32 1, i32 1, i32 1, i32 1, i32 1, i32 1>, %24 ], [ %42, %30 ]
  %35 = phi <8 x i32> [ <i32 1, i32 1, i32 1, i32 1, i32 1, i32 1, i32 1, i32 1>, %24 ], [ %43, %30 ]
  %36 = phi <8 x i32> [ %29, %24 ], [ %45, %30 ]
  %37 = add <8 x i32> %36, <i32 -8, i32 -8, i32 -8, i32 -8, i32 -8, i32 -8, i32 -8, i32 -8>
  %38 = add <8 x i32> %36, <i32 -16, i32 -16, i32 -16, i32 -16, i32 -16, i32 -16, i32 -16, i32 -16>
  %39 = add <8 x i32> %36, <i32 -24, i32 -24, i32 -24, i32 -24, i32 -24, i32 -24, i32 -24, i32 -24>
  %40 = mul <8 x i32> %36, %32
  %41 = mul <8 x i32> %37, %33
  %42 = mul <8 x i32> %38, %34
  %43 = mul <8 x i32> %39, %35
  %44 = add nuw i32 %31, 32
  %45 = add <8 x i32> %36, <i32 -32, i32 -32, i32 -32, i32 -32, i32 -32, i32 -32, i32 -32, i32 -32>
  %46 = icmp eq i32 %44, %25
  br i1 %46, label %47, label %30, !llvm.loop !19

47:                                               ; preds = %30
  %48 = mul <8 x i32> %41, %40
  %49 = mul <8 x i32> %42, %48
  %50 = mul <8 x i32> %43, %49
  %51 = call i32 @llvm.vector.reduce.mul.v8i32(<8 x i32> %50)
  %52 = icmp eq i32 %22, %25
  br i1 %52, label %62, label %53

53:                                               ; preds = %47, %21
  %54 = phi i32 [ 1, %21 ], [ %51, %47 ]
  %55 = phi i32 [ %19, %21 ], [ %26, %47 ]
  br label %56

56:                                               ; preds = %53, %56
  %57 = phi i32 [ %59, %56 ], [ %54, %53 ]
  %58 = phi i32 [ %60, %56 ], [ %55, %53 ]
  %59 = mul nuw nsw i32 %58, %57
  %60 = add nsw i32 %58, -1
  %61 = icmp ugt i32 %58, 2
  br i1 %61, label %56, label %62, !llvm.loop !21

62:                                               ; preds = %56, %47, %18
  %63 = phi i32 [ 1, %18 ], [ %51, %47 ], [ %59, %56 ]
  %64 = call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.10, i32 noundef %19, i32 noundef %63)
  br label %178

65:                                               ; preds = %0
  %66 = load i32, ptr %2, align 4, !tbaa !11
  %67 = icmp slt i32 %66, 2
  br i1 %67, label %109, label %68

68:                                               ; preds = %65
  %69 = add nsw i32 %66, -1
  %70 = icmp ult i32 %66, 33
  br i1 %70, label %100, label %71

71:                                               ; preds = %68
  %72 = and i32 %69, -32
  %73 = sub i32 %66, %72
  %74 = insertelement <8 x i32> poison, i32 %66, i64 0
  %75 = shufflevector <8 x i32> %74, <8 x i32> poison, <8 x i32> zeroinitializer
  %76 = add nsw <8 x i32> %75, <i32 0, i32 -1, i32 -2, i32 -3, i32 -4, i32 -5, i32 -6, i32 -7>
  br label %77

77:                                               ; preds = %77, %71
  %78 = phi i32 [ 0, %71 ], [ %91, %77 ]
  %79 = phi <8 x i32> [ %76, %71 ], [ %92, %77 ]
  %80 = phi <8 x i32> [ <i32 1, i32 1, i32 1, i32 1, i32 1, i32 1, i32 1, i32 1>, %71 ], [ %87, %77 ]
  %81 = phi <8 x i32> [ <i32 1, i32 1, i32 1, i32 1, i32 1, i32 1, i32 1, i32 1>, %71 ], [ %88, %77 ]
  %82 = phi <8 x i32> [ <i32 1, i32 1, i32 1, i32 1, i32 1, i32 1, i32 1, i32 1>, %71 ], [ %89, %77 ]
  %83 = phi <8 x i32> [ <i32 1, i32 1, i32 1, i32 1, i32 1, i32 1, i32 1, i32 1>, %71 ], [ %90, %77 ]
  %84 = add <8 x i32> %79, <i32 -8, i32 -8, i32 -8, i32 -8, i32 -8, i32 -8, i32 -8, i32 -8>
  %85 = add <8 x i32> %79, <i32 -16, i32 -16, i32 -16, i32 -16, i32 -16, i32 -16, i32 -16, i32 -16>
  %86 = add <8 x i32> %79, <i32 -24, i32 -24, i32 -24, i32 -24, i32 -24, i32 -24, i32 -24, i32 -24>
  %87 = mul <8 x i32> %80, %79
  %88 = mul <8 x i32> %81, %84
  %89 = mul <8 x i32> %82, %85
  %90 = mul <8 x i32> %83, %86
  %91 = add nuw i32 %78, 32
  %92 = add <8 x i32> %79, <i32 -32, i32 -32, i32 -32, i32 -32, i32 -32, i32 -32, i32 -32, i32 -32>
  %93 = icmp eq i32 %91, %72
  br i1 %93, label %94, label %77, !llvm.loop !22

94:                                               ; preds = %77
  %95 = mul <8 x i32> %88, %87
  %96 = mul <8 x i32> %89, %95
  %97 = mul <8 x i32> %90, %96
  %98 = call i32 @llvm.vector.reduce.mul.v8i32(<8 x i32> %97)
  %99 = icmp eq i32 %69, %72
  br i1 %99, label %109, label %100

100:                                              ; preds = %94, %68
  %101 = phi i32 [ %66, %68 ], [ %73, %94 ]
  %102 = phi i32 [ 1, %68 ], [ %98, %94 ]
  br label %103

103:                                              ; preds = %100, %103
  %104 = phi i32 [ %106, %103 ], [ %101, %100 ]
  %105 = phi i32 [ %107, %103 ], [ %102, %100 ]
  %106 = add nsw i32 %104, -1
  %107 = mul nuw nsw i32 %105, %104
  %108 = icmp ult i32 %104, 3
  br i1 %108, label %109, label %103, !llvm.loop !23

109:                                              ; preds = %103, %94, %65
  %110 = phi i32 [ 1, %65 ], [ %98, %94 ], [ %107, %103 ]
  %111 = call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.11, i32 noundef %66, i32 noundef %110)
  br label %178

112:                                              ; preds = %0
  %113 = load i32, ptr %2, align 4, !tbaa !11
  %114 = call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.12, i32 noundef %113)
  %115 = load i32, ptr %2, align 4, !tbaa !11
  %116 = icmp slt i32 %115, 1
  br i1 %116, label %117, label %119

117:                                              ; preds = %155, %112
  %118 = call i32 @putchar(i32 10)
  br label %178

119:                                              ; preds = %112, %155
  %120 = phi i32 [ %161, %155 ], [ 0, %112 ]
  %121 = phi i32 [ %158, %155 ], [ 1, %112 ]
  %122 = icmp eq i32 %121, 1
  br i1 %122, label %155, label %123

123:                                              ; preds = %119
  %124 = add i32 %120, -1
  %125 = and i32 %120, 7
  %126 = icmp ult i32 %124, 7
  br i1 %126, label %143, label %127

127:                                              ; preds = %123
  %128 = and i32 %120, -8
  br label %129

129:                                              ; preds = %129, %127
  %130 = phi i32 [ 1, %127 ], [ %140, %129 ]
  %131 = phi i32 [ 0, %127 ], [ %139, %129 ]
  %132 = phi i32 [ 0, %127 ], [ %141, %129 ]
  %133 = add nsw i32 %131, %130
  %134 = add nsw i32 %130, %133
  %135 = add nsw i32 %133, %134
  %136 = add nsw i32 %134, %135
  %137 = add nsw i32 %135, %136
  %138 = add nsw i32 %136, %137
  %139 = add nsw i32 %137, %138
  %140 = add nsw i32 %138, %139
  %141 = add i32 %132, 8
  %142 = icmp eq i32 %141, %128
  br i1 %142, label %143, label %129, !llvm.loop !24

143:                                              ; preds = %129, %123
  %144 = phi i32 [ poison, %123 ], [ %140, %129 ]
  %145 = phi i32 [ 1, %123 ], [ %140, %129 ]
  %146 = phi i32 [ 0, %123 ], [ %139, %129 ]
  %147 = icmp eq i32 %125, 0
  br i1 %147, label %155, label %148

148:                                              ; preds = %143, %148
  %149 = phi i32 [ %152, %148 ], [ %145, %143 ]
  %150 = phi i32 [ %149, %148 ], [ %146, %143 ]
  %151 = phi i32 [ %153, %148 ], [ 0, %143 ]
  %152 = add nsw i32 %150, %149
  %153 = add i32 %151, 1
  %154 = icmp eq i32 %153, %125
  br i1 %154, label %155, label %148, !llvm.loop !25

155:                                              ; preds = %143, %148, %119
  %156 = phi i32 [ 1, %119 ], [ %144, %143 ], [ %152, %148 ]
  %157 = call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.13, i32 noundef %156)
  %158 = add nuw nsw i32 %121, 1
  %159 = load i32, ptr %2, align 4, !tbaa !11
  %160 = icmp slt i32 %121, %159
  %161 = add i32 %120, 1
  br i1 %160, label %119, label %117, !llvm.loop !27

162:                                              ; preds = %0
  %163 = load i32, ptr %2, align 4, !tbaa !11
  %164 = call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.15, i32 noundef %163)
  %165 = load i32, ptr %2, align 4, !tbaa !11
  %166 = icmp slt i32 %165, 1
  br i1 %166, label %167, label %169

167:                                              ; preds = %169, %162
  %168 = call i32 @putchar(i32 10)
  br label %178

169:                                              ; preds = %162, %169
  %170 = phi i32 [ %173, %169 ], [ 1, %162 ]
  %171 = call i32 @fibonacci_recursive(i32 noundef %170)
  %172 = call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.13, i32 noundef %171)
  %173 = add nuw nsw i32 %170, 1
  %174 = load i32, ptr %2, align 4, !tbaa !11
  %175 = icmp slt i32 %170, %174
  br i1 %175, label %169, label %167, !llvm.loop !28

176:                                              ; preds = %0
  %177 = call i32 @puts(ptr nonnull dereferenceable(1) @str.21)
  br label %178

178:                                              ; preds = %176, %167, %117, %109, %62
  call void @llvm.lifetime.end.p0(i64 4, ptr nonnull %2) #12
  call void @llvm.lifetime.end.p0(i64 4, ptr nonnull %1) #12
  ret i32 0
}

; Function Attrs: nofree nounwind
declare noundef i32 @printf(ptr nocapture noundef readonly, ...) local_unnamed_addr #6

; Function Attrs: nofree nounwind
declare noundef i32 @__isoc99_scanf(ptr nocapture noundef readonly, ...) local_unnamed_addr #6

; Function Attrs: nofree norecurse nosync nounwind sspstrong memory(none) uwtable
define dso_local range(i32 1, -2147483648) i32 @factorial_iterative(i32 noundef %0) local_unnamed_addr #5 {
  %2 = icmp sgt i32 %0, 1
  br i1 %2, label %3, label %44

3:                                                ; preds = %1
  %4 = add nsw i32 %0, -1
  %5 = icmp ult i32 %0, 33
  br i1 %5, label %35, label %6

6:                                                ; preds = %3
  %7 = and i32 %4, -32
  %8 = sub i32 %0, %7
  %9 = insertelement <8 x i32> poison, i32 %0, i64 0
  %10 = shufflevector <8 x i32> %9, <8 x i32> poison, <8 x i32> zeroinitializer
  %11 = add nsw <8 x i32> %10, <i32 0, i32 -1, i32 -2, i32 -3, i32 -4, i32 -5, i32 -6, i32 -7>
  br label %12

12:                                               ; preds = %12, %6
  %13 = phi i32 [ 0, %6 ], [ %26, %12 ]
  %14 = phi <8 x i32> [ <i32 1, i32 1, i32 1, i32 1, i32 1, i32 1, i32 1, i32 1>, %6 ], [ %22, %12 ]
  %15 = phi <8 x i32> [ <i32 1, i32 1, i32 1, i32 1, i32 1, i32 1, i32 1, i32 1>, %6 ], [ %23, %12 ]
  %16 = phi <8 x i32> [ <i32 1, i32 1, i32 1, i32 1, i32 1, i32 1, i32 1, i32 1>, %6 ], [ %24, %12 ]
  %17 = phi <8 x i32> [ <i32 1, i32 1, i32 1, i32 1, i32 1, i32 1, i32 1, i32 1>, %6 ], [ %25, %12 ]
  %18 = phi <8 x i32> [ %11, %6 ], [ %27, %12 ]
  %19 = add <8 x i32> %18, <i32 -8, i32 -8, i32 -8, i32 -8, i32 -8, i32 -8, i32 -8, i32 -8>
  %20 = add <8 x i32> %18, <i32 -16, i32 -16, i32 -16, i32 -16, i32 -16, i32 -16, i32 -16, i32 -16>
  %21 = add <8 x i32> %18, <i32 -24, i32 -24, i32 -24, i32 -24, i32 -24, i32 -24, i32 -24, i32 -24>
  %22 = mul <8 x i32> %14, %18
  %23 = mul <8 x i32> %15, %19
  %24 = mul <8 x i32> %16, %20
  %25 = mul <8 x i32> %17, %21
  %26 = add nuw i32 %13, 32
  %27 = add <8 x i32> %18, <i32 -32, i32 -32, i32 -32, i32 -32, i32 -32, i32 -32, i32 -32, i32 -32>
  %28 = icmp eq i32 %26, %7
  br i1 %28, label %29, label %12, !llvm.loop !29

29:                                               ; preds = %12
  %30 = mul <8 x i32> %23, %22
  %31 = mul <8 x i32> %24, %30
  %32 = mul <8 x i32> %25, %31
  %33 = tail call i32 @llvm.vector.reduce.mul.v8i32(<8 x i32> %32)
  %34 = icmp eq i32 %4, %7
  br i1 %34, label %44, label %35

35:                                               ; preds = %29, %3
  %36 = phi i32 [ 1, %3 ], [ %33, %29 ]
  %37 = phi i32 [ %0, %3 ], [ %8, %29 ]
  br label %38

38:                                               ; preds = %35, %38
  %39 = phi i32 [ %41, %38 ], [ %36, %35 ]
  %40 = phi i32 [ %42, %38 ], [ %37, %35 ]
  %41 = mul nuw nsw i32 %39, %40
  %42 = add nsw i32 %40, -1
  %43 = icmp ugt i32 %40, 2
  br i1 %43, label %38, label %44, !llvm.loop !30

44:                                               ; preds = %38, %29, %1
  %45 = phi i32 [ 1, %1 ], [ %33, %29 ], [ %41, %38 ]
  ret i32 %45
}

; Function Attrs: nofree norecurse nosync nounwind sspstrong memory(none) uwtable
define dso_local range(i32 1, -2147483648) i32 @factorial_recursive(i32 noundef %0) local_unnamed_addr #5 {
  %2 = icmp slt i32 %0, 2
  br i1 %2, label %44, label %3

3:                                                ; preds = %1
  %4 = add nsw i32 %0, -1
  %5 = icmp ult i32 %0, 33
  br i1 %5, label %35, label %6

6:                                                ; preds = %3
  %7 = and i32 %4, -32
  %8 = sub i32 %0, %7
  %9 = insertelement <8 x i32> poison, i32 %0, i64 0
  %10 = shufflevector <8 x i32> %9, <8 x i32> poison, <8 x i32> zeroinitializer
  %11 = add nsw <8 x i32> %10, <i32 0, i32 -1, i32 -2, i32 -3, i32 -4, i32 -5, i32 -6, i32 -7>
  br label %12

12:                                               ; preds = %12, %6
  %13 = phi i32 [ 0, %6 ], [ %26, %12 ]
  %14 = phi <8 x i32> [ %11, %6 ], [ %27, %12 ]
  %15 = phi <8 x i32> [ <i32 1, i32 1, i32 1, i32 1, i32 1, i32 1, i32 1, i32 1>, %6 ], [ %22, %12 ]
  %16 = phi <8 x i32> [ <i32 1, i32 1, i32 1, i32 1, i32 1, i32 1, i32 1, i32 1>, %6 ], [ %23, %12 ]
  %17 = phi <8 x i32> [ <i32 1, i32 1, i32 1, i32 1, i32 1, i32 1, i32 1, i32 1>, %6 ], [ %24, %12 ]
  %18 = phi <8 x i32> [ <i32 1, i32 1, i32 1, i32 1, i32 1, i32 1, i32 1, i32 1>, %6 ], [ %25, %12 ]
  %19 = add <8 x i32> %14, <i32 -8, i32 -8, i32 -8, i32 -8, i32 -8, i32 -8, i32 -8, i32 -8>
  %20 = add <8 x i32> %14, <i32 -16, i32 -16, i32 -16, i32 -16, i32 -16, i32 -16, i32 -16, i32 -16>
  %21 = add <8 x i32> %14, <i32 -24, i32 -24, i32 -24, i32 -24, i32 -24, i32 -24, i32 -24, i32 -24>
  %22 = mul <8 x i32> %14, %15
  %23 = mul <8 x i32> %19, %16
  %24 = mul <8 x i32> %20, %17
  %25 = mul <8 x i32> %21, %18
  %26 = add nuw i32 %13, 32
  %27 = add <8 x i32> %14, <i32 -32, i32 -32, i32 -32, i32 -32, i32 -32, i32 -32, i32 -32, i32 -32>
  %28 = icmp eq i32 %26, %7
  br i1 %28, label %29, label %12, !llvm.loop !31

29:                                               ; preds = %12
  %30 = mul <8 x i32> %23, %22
  %31 = mul <8 x i32> %24, %30
  %32 = mul <8 x i32> %25, %31
  %33 = tail call i32 @llvm.vector.reduce.mul.v8i32(<8 x i32> %32)
  %34 = icmp eq i32 %4, %7
  br i1 %34, label %44, label %35

35:                                               ; preds = %29, %3
  %36 = phi i32 [ %0, %3 ], [ %8, %29 ]
  %37 = phi i32 [ 1, %3 ], [ %33, %29 ]
  br label %38

38:                                               ; preds = %35, %38
  %39 = phi i32 [ %41, %38 ], [ %36, %35 ]
  %40 = phi i32 [ %42, %38 ], [ %37, %35 ]
  %41 = add nsw i32 %39, -1
  %42 = mul nuw nsw i32 %39, %40
  %43 = icmp ult i32 %39, 3
  br i1 %43, label %44, label %38, !llvm.loop !32

44:                                               ; preds = %38, %29, %1
  %45 = phi i32 [ 1, %1 ], [ %33, %29 ], [ %42, %38 ]
  ret i32 %45
}

; Function Attrs: nofree norecurse nosync nounwind sspstrong memory(none) uwtable
define dso_local i32 @fibonacci_iterative(i32 noundef %0) local_unnamed_addr #5 {
  %2 = icmp slt i32 %0, 1
  br i1 %2, label %38, label %3

3:                                                ; preds = %1
  %4 = icmp eq i32 %0, 1
  br i1 %4, label %38, label %5

5:                                                ; preds = %3
  %6 = add nsw i32 %0, -1
  %7 = add nsw i32 %0, -2
  %8 = and i32 %6, 7
  %9 = icmp ult i32 %7, 7
  br i1 %9, label %26, label %10

10:                                               ; preds = %5
  %11 = and i32 %6, -8
  br label %12

12:                                               ; preds = %12, %10
  %13 = phi i32 [ 1, %10 ], [ %23, %12 ]
  %14 = phi i32 [ 0, %10 ], [ %22, %12 ]
  %15 = phi i32 [ 0, %10 ], [ %24, %12 ]
  %16 = add nsw i32 %13, %14
  %17 = add nsw i32 %16, %13
  %18 = add nsw i32 %17, %16
  %19 = add nsw i32 %18, %17
  %20 = add nsw i32 %19, %18
  %21 = add nsw i32 %20, %19
  %22 = add nsw i32 %21, %20
  %23 = add nsw i32 %22, %21
  %24 = add i32 %15, 8
  %25 = icmp eq i32 %24, %11
  br i1 %25, label %26, label %12, !llvm.loop !24

26:                                               ; preds = %12, %5
  %27 = phi i32 [ poison, %5 ], [ %23, %12 ]
  %28 = phi i32 [ 1, %5 ], [ %23, %12 ]
  %29 = phi i32 [ 0, %5 ], [ %22, %12 ]
  %30 = icmp eq i32 %8, 0
  br i1 %30, label %38, label %31

31:                                               ; preds = %26, %31
  %32 = phi i32 [ %35, %31 ], [ %28, %26 ]
  %33 = phi i32 [ %32, %31 ], [ %29, %26 ]
  %34 = phi i32 [ %36, %31 ], [ 0, %26 ]
  %35 = add nsw i32 %32, %33
  %36 = add i32 %34, 1
  %37 = icmp eq i32 %36, %8
  br i1 %37, label %38, label %31, !llvm.loop !33

38:                                               ; preds = %26, %31, %3, %1
  %39 = phi i32 [ 0, %1 ], [ 1, %3 ], [ %27, %26 ], [ %35, %31 ]
  ret i32 %39
}

; Function Attrs: nofree nosync nounwind sspstrong memory(none) uwtable
define dso_local i32 @fibonacci_recursive(i32 noundef %0) local_unnamed_addr #7 {
  %2 = icmp slt i32 %0, 1
  br i1 %2, label %15, label %3

3:                                                ; preds = %1
  %4 = icmp ult i32 %0, 3
  br i1 %4, label %15, label %5

5:                                                ; preds = %3, %5
  %6 = phi i32 [ %11, %5 ], [ 0, %3 ]
  %7 = phi i32 [ %10, %5 ], [ %0, %3 ]
  %8 = add nsw i32 %7, -1
  %9 = tail call i32 @fibonacci_recursive(i32 noundef %8)
  %10 = add nsw i32 %7, -2
  %11 = add nsw i32 %9, %6
  %12 = icmp ult i32 %10, 3
  br i1 %12, label %13, label %5

13:                                               ; preds = %5
  %14 = add nsw i32 %11, 1
  br label %15

15:                                               ; preds = %3, %13, %1
  %16 = phi i32 [ 0, %1 ], [ %14, %13 ], [ 1, %3 ]
  ret i32 %16
}

; Function Attrs: nofree nounwind
declare noundef i32 @puts(ptr nocapture noundef readonly) local_unnamed_addr #8

; Function Attrs: nofree nounwind
declare noundef i32 @putchar(i32 noundef) local_unnamed_addr #8

; Function Attrs: nocallback nofree nounwind willreturn memory(argmem: write)
declare void @llvm.memset.p0.i64(ptr nocapture writeonly, i8, i64, i1 immarg) #9

; Function Attrs: nocallback nofree nosync nounwind speculatable willreturn memory(none)
declare i32 @llvm.vector.reduce.mul.v8i32(<8 x i32>) #10

attributes #0 = { nofree nosync nounwind sspstrong memory(readwrite, inaccessiblemem: none) uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="skylake" "target-features"="+64bit,+adx,+aes,+avx,+avx2,+bmi,+bmi2,+clflushopt,+cmov,+crc32,+cx16,+cx8,+f16c,+fma,+fsgsbase,+fxsr,+invpcid,+lzcnt,+mmx,+movbe,+pclmul,+popcnt,+prfchw,+rdrnd,+rdseed,+sahf,+sgx,+sse,+sse2,+sse3,+sse4.1,+sse4.2,+ssse3,+x87,+xsave,+xsavec,+xsaveopt,+xsaves,-amx-bf16,-amx-complex,-amx-fp16,-amx-int8,-amx-tile,-avx10.1-256,-avx10.1-512,-avx512bf16,-avx512bitalg,-avx512bw,-avx512cd,-avx512dq,-avx512f,-avx512fp16,-avx512ifma,-avx512vbmi,-avx512vbmi2,-avx512vl,-avx512vnni,-avx512vp2intersect,-avx512vpopcntdq,-avxifma,-avxneconvert,-avxvnni,-avxvnniint16,-avxvnniint8,-ccmp,-cf,-cldemote,-clwb,-clzero,-cmpccxadd,-egpr,-enqcmd,-fma4,-gfni,-hreset,-kl,-lwp,-movdir64b,-movdiri,-mwaitx,-ndd,-pconfig,-pku,-ppx,-prefetchi,-ptwrite,-push2pop2,-raoint,-rdpid,-rdpru,-rtm,-serialize,-sha,-sha512,-shstk,-sm3,-sm4,-sse4a,-tbm,-tsxldtrk,-uintr,-usermsr,-vaes,-vpclmulqdq,-waitpkg,-wbnoinvd,-widekl,-xop" }
attributes #1 = { nounwind sspstrong uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="skylake" "target-features"="+64bit,+adx,+aes,+avx,+avx2,+bmi,+bmi2,+clflushopt,+cmov,+crc32,+cx16,+cx8,+f16c,+fma,+fsgsbase,+fxsr,+invpcid,+lzcnt,+mmx,+movbe,+pclmul,+popcnt,+prfchw,+rdrnd,+rdseed,+sahf,+sgx,+sse,+sse2,+sse3,+sse4.1,+sse4.2,+ssse3,+x87,+xsave,+xsavec,+xsaveopt,+xsaves,-amx-bf16,-amx-complex,-amx-fp16,-amx-int8,-amx-tile,-avx10.1-256,-avx10.1-512,-avx512bf16,-avx512bitalg,-avx512bw,-avx512cd,-avx512dq,-avx512f,-avx512fp16,-avx512ifma,-avx512vbmi,-avx512vbmi2,-avx512vl,-avx512vnni,-avx512vp2intersect,-avx512vpopcntdq,-avxifma,-avxneconvert,-avxvnni,-avxvnniint16,-avxvnniint8,-ccmp,-cf,-cldemote,-clwb,-clzero,-cmpccxadd,-egpr,-enqcmd,-fma4,-gfni,-hreset,-kl,-lwp,-movdir64b,-movdiri,-mwaitx,-ndd,-pconfig,-pku,-ppx,-prefetchi,-ptwrite,-push2pop2,-raoint,-rdpid,-rdpru,-rtm,-serialize,-sha,-sha512,-shstk,-sm3,-sm4,-sse4a,-tbm,-tsxldtrk,-uintr,-usermsr,-vaes,-vpclmulqdq,-waitpkg,-wbnoinvd,-widekl,-xop" }
attributes #2 = { mustprogress nofree nounwind willreturn allockind("alloc,uninitialized") allocsize(0) memory(inaccessiblemem: readwrite) "alloc-family"="malloc" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="skylake" "target-features"="+64bit,+adx,+aes,+avx,+avx2,+bmi,+bmi2,+clflushopt,+cmov,+crc32,+cx16,+cx8,+f16c,+fma,+fsgsbase,+fxsr,+invpcid,+lzcnt,+mmx,+movbe,+pclmul,+popcnt,+prfchw,+rdrnd,+rdseed,+sahf,+sgx,+sse,+sse2,+sse3,+sse4.1,+sse4.2,+ssse3,+x87,+xsave,+xsavec,+xsaveopt,+xsaves,-amx-bf16,-amx-complex,-amx-fp16,-amx-int8,-amx-tile,-avx10.1-256,-avx10.1-512,-avx512bf16,-avx512bitalg,-avx512bw,-avx512cd,-avx512dq,-avx512f,-avx512fp16,-avx512ifma,-avx512vbmi,-avx512vbmi2,-avx512vl,-avx512vnni,-avx512vp2intersect,-avx512vpopcntdq,-avxifma,-avxneconvert,-avxvnni,-avxvnniint16,-avxvnniint8,-ccmp,-cf,-cldemote,-clwb,-clzero,-cmpccxadd,-egpr,-enqcmd,-fma4,-gfni,-hreset,-kl,-lwp,-movdir64b,-movdiri,-mwaitx,-ndd,-pconfig,-pku,-ppx,-prefetchi,-ptwrite,-push2pop2,-raoint,-rdpid,-rdpru,-rtm,-serialize,-sha,-sha512,-shstk,-sm3,-sm4,-sse4a,-tbm,-tsxldtrk,-uintr,-usermsr,-vaes,-vpclmulqdq,-waitpkg,-wbnoinvd,-widekl,-xop" }
attributes #3 = { mustprogress nocallback nofree nosync nounwind willreturn memory(argmem: readwrite) }
attributes #4 = { mustprogress nounwind willreturn allockind("free") memory(argmem: readwrite, inaccessiblemem: readwrite) "alloc-family"="malloc" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="skylake" "target-features"="+64bit,+adx,+aes,+avx,+avx2,+bmi,+bmi2,+clflushopt,+cmov,+crc32,+cx16,+cx8,+f16c,+fma,+fsgsbase,+fxsr,+invpcid,+lzcnt,+mmx,+movbe,+pclmul,+popcnt,+prfchw,+rdrnd,+rdseed,+sahf,+sgx,+sse,+sse2,+sse3,+sse4.1,+sse4.2,+ssse3,+x87,+xsave,+xsavec,+xsaveopt,+xsaves,-amx-bf16,-amx-complex,-amx-fp16,-amx-int8,-amx-tile,-avx10.1-256,-avx10.1-512,-avx512bf16,-avx512bitalg,-avx512bw,-avx512cd,-avx512dq,-avx512f,-avx512fp16,-avx512ifma,-avx512vbmi,-avx512vbmi2,-avx512vl,-avx512vnni,-avx512vp2intersect,-avx512vpopcntdq,-avxifma,-avxneconvert,-avxvnni,-avxvnniint16,-avxvnniint8,-ccmp,-cf,-cldemote,-clwb,-clzero,-cmpccxadd,-egpr,-enqcmd,-fma4,-gfni,-hreset,-kl,-lwp,-movdir64b,-movdiri,-mwaitx,-ndd,-pconfig,-pku,-ppx,-prefetchi,-ptwrite,-push2pop2,-raoint,-rdpid,-rdpru,-rtm,-serialize,-sha,-sha512,-shstk,-sm3,-sm4,-sse4a,-tbm,-tsxldtrk,-uintr,-usermsr,-vaes,-vpclmulqdq,-waitpkg,-wbnoinvd,-widekl,-xop" }
attributes #5 = { nofree norecurse nosync nounwind sspstrong memory(none) uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="skylake" "target-features"="+64bit,+adx,+aes,+avx,+avx2,+bmi,+bmi2,+clflushopt,+cmov,+crc32,+cx16,+cx8,+f16c,+fma,+fsgsbase,+fxsr,+invpcid,+lzcnt,+mmx,+movbe,+pclmul,+popcnt,+prfchw,+rdrnd,+rdseed,+sahf,+sgx,+sse,+sse2,+sse3,+sse4.1,+sse4.2,+ssse3,+x87,+xsave,+xsavec,+xsaveopt,+xsaves,-amx-bf16,-amx-complex,-amx-fp16,-amx-int8,-amx-tile,-avx10.1-256,-avx10.1-512,-avx512bf16,-avx512bitalg,-avx512bw,-avx512cd,-avx512dq,-avx512f,-avx512fp16,-avx512ifma,-avx512vbmi,-avx512vbmi2,-avx512vl,-avx512vnni,-avx512vp2intersect,-avx512vpopcntdq,-avxifma,-avxneconvert,-avxvnni,-avxvnniint16,-avxvnniint8,-ccmp,-cf,-cldemote,-clwb,-clzero,-cmpccxadd,-egpr,-enqcmd,-fma4,-gfni,-hreset,-kl,-lwp,-movdir64b,-movdiri,-mwaitx,-ndd,-pconfig,-pku,-ppx,-prefetchi,-ptwrite,-push2pop2,-raoint,-rdpid,-rdpru,-rtm,-serialize,-sha,-sha512,-shstk,-sm3,-sm4,-sse4a,-tbm,-tsxldtrk,-uintr,-usermsr,-vaes,-vpclmulqdq,-waitpkg,-wbnoinvd,-widekl,-xop" }
attributes #6 = { nofree nounwind "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="skylake" "target-features"="+64bit,+adx,+aes,+avx,+avx2,+bmi,+bmi2,+clflushopt,+cmov,+crc32,+cx16,+cx8,+f16c,+fma,+fsgsbase,+fxsr,+invpcid,+lzcnt,+mmx,+movbe,+pclmul,+popcnt,+prfchw,+rdrnd,+rdseed,+sahf,+sgx,+sse,+sse2,+sse3,+sse4.1,+sse4.2,+ssse3,+x87,+xsave,+xsavec,+xsaveopt,+xsaves,-amx-bf16,-amx-complex,-amx-fp16,-amx-int8,-amx-tile,-avx10.1-256,-avx10.1-512,-avx512bf16,-avx512bitalg,-avx512bw,-avx512cd,-avx512dq,-avx512f,-avx512fp16,-avx512ifma,-avx512vbmi,-avx512vbmi2,-avx512vl,-avx512vnni,-avx512vp2intersect,-avx512vpopcntdq,-avxifma,-avxneconvert,-avxvnni,-avxvnniint16,-avxvnniint8,-ccmp,-cf,-cldemote,-clwb,-clzero,-cmpccxadd,-egpr,-enqcmd,-fma4,-gfni,-hreset,-kl,-lwp,-movdir64b,-movdiri,-mwaitx,-ndd,-pconfig,-pku,-ppx,-prefetchi,-ptwrite,-push2pop2,-raoint,-rdpid,-rdpru,-rtm,-serialize,-sha,-sha512,-shstk,-sm3,-sm4,-sse4a,-tbm,-tsxldtrk,-uintr,-usermsr,-vaes,-vpclmulqdq,-waitpkg,-wbnoinvd,-widekl,-xop" }
attributes #7 = { nofree nosync nounwind sspstrong memory(none) uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="skylake" "target-features"="+64bit,+adx,+aes,+avx,+avx2,+bmi,+bmi2,+clflushopt,+cmov,+crc32,+cx16,+cx8,+f16c,+fma,+fsgsbase,+fxsr,+invpcid,+lzcnt,+mmx,+movbe,+pclmul,+popcnt,+prfchw,+rdrnd,+rdseed,+sahf,+sgx,+sse,+sse2,+sse3,+sse4.1,+sse4.2,+ssse3,+x87,+xsave,+xsavec,+xsaveopt,+xsaves,-amx-bf16,-amx-complex,-amx-fp16,-amx-int8,-amx-tile,-avx10.1-256,-avx10.1-512,-avx512bf16,-avx512bitalg,-avx512bw,-avx512cd,-avx512dq,-avx512f,-avx512fp16,-avx512ifma,-avx512vbmi,-avx512vbmi2,-avx512vl,-avx512vnni,-avx512vp2intersect,-avx512vpopcntdq,-avxifma,-avxneconvert,-avxvnni,-avxvnniint16,-avxvnniint8,-ccmp,-cf,-cldemote,-clwb,-clzero,-cmpccxadd,-egpr,-enqcmd,-fma4,-gfni,-hreset,-kl,-lwp,-movdir64b,-movdiri,-mwaitx,-ndd,-pconfig,-pku,-ppx,-prefetchi,-ptwrite,-push2pop2,-raoint,-rdpid,-rdpru,-rtm,-serialize,-sha,-sha512,-shstk,-sm3,-sm4,-sse4a,-tbm,-tsxldtrk,-uintr,-usermsr,-vaes,-vpclmulqdq,-waitpkg,-wbnoinvd,-widekl,-xop" }
attributes #8 = { nofree nounwind }
attributes #9 = { nocallback nofree nounwind willreturn memory(argmem: write) }
attributes #10 = { nocallback nofree nosync nounwind speculatable willreturn memory(none) }
attributes #11 = { nounwind allocsize(0) }
attributes #12 = { nounwind }

!llvm.module.flags = !{!0, !1, !2, !3, !4, !5}
!llvm.ident = !{!6}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 8, !"PIC Level", i32 2}
!2 = !{i32 7, !"PIE Level", i32 2}
!3 = !{i32 7, !"uwtable", i32 2}
!4 = !{i32 1, !"ThinLTO", i32 0}
!5 = !{i32 1, !"EnableSplitLTOUnit", i32 1}
!6 = !{!"clang version 19.1.7"}
!7 = !{!8, !8, i64 0}
!8 = !{!"any pointer", !9, i64 0}
!9 = !{!"omnipotent char", !10, i64 0}
!10 = !{!"Simple C/C++ TBAA"}
!11 = !{!12, !12, i64 0}
!12 = !{!"int", !9, i64 0}
!13 = distinct !{!13, !14, !15}
!14 = !{!"llvm.loop.isvectorized", i32 1}
!15 = !{!"llvm.loop.unroll.runtime.disable"}
!16 = distinct !{!16, !15, !14}
!17 = distinct !{!17, !14, !15}
!18 = distinct !{!18, !15, !14}
!19 = distinct !{!19, !20, !14, !15}
!20 = !{!"llvm.loop.mustprogress"}
!21 = distinct !{!21, !20, !15, !14}
!22 = distinct !{!22, !14, !15}
!23 = distinct !{!23, !15, !14}
!24 = distinct !{!24, !20}
!25 = distinct !{!25, !26}
!26 = !{!"llvm.loop.unroll.disable"}
!27 = distinct !{!27, !20}
!28 = distinct !{!28, !20}
!29 = distinct !{!29, !20, !14, !15}
!30 = distinct !{!30, !20, !15, !14}
!31 = distinct !{!31, !14, !15}
!32 = distinct !{!32, !15, !14}
!33 = distinct !{!33, !26}

^0 = module: (path: "[Regular LTO]", hash: (0, 0, 0, 0, 0))
^1 = gv: (name: ".str.11", summaries: (variable: (module: ^0, flags: (linkage: private, visibility: default, notEligibleToImport: 1, live: 0, dsoLocal: 1, canAutoHide: 0, importType: definition), varFlags: (readonly: 1, writeonly: 0, constant: 1)))) ; guid = 880700377235718516
^2 = gv: (name: "putchar") ; guid = 1377009889143723207
^3 = gv: (name: "str.21", summaries: (variable: (module: ^0, flags: (linkage: private, visibility: default, notEligibleToImport: 1, live: 0, dsoLocal: 1, canAutoHide: 0, importType: definition), varFlags: (readonly: 1, writeonly: 0, constant: 1)))) ; guid = 1694359528243534698
^4 = gv: (name: "fibonacci_memo", summaries: (function: (module: ^0, flags: (linkage: external, visibility: default, notEligibleToImport: 1, live: 0, dsoLocal: 1, canAutoHide: 0, importType: definition), insts: 21, funcFlags: (readNone: 0, readOnly: 0, noRecurse: 0, returnDoesNotAlias: 0, noInline: 0, alwaysInline: 0, noUnwind: 1, mayThrow: 0, hasUnknownCall: 0, mustBeUnreachable: 0), calls: ((callee: ^4, relbf: 96, tail: 1)), refs: (^12)))) ; guid = 2118582588610832611
^5 = gv: (name: "malloc") ; guid = 2336192559129972258
^6 = gv: (name: ".str.7", summaries: (variable: (module: ^0, flags: (linkage: private, visibility: default, notEligibleToImport: 1, live: 0, dsoLocal: 1, canAutoHide: 0, importType: definition), varFlags: (readonly: 1, writeonly: 0, constant: 1)))) ; guid = 3134923074148782846
^7 = gv: (name: "factorial_recursive", summaries: (function: (module: ^0, flags: (linkage: external, visibility: default, notEligibleToImport: 1, live: 0, dsoLocal: 1, canAutoHide: 0, importType: definition), insts: 45, funcFlags: (readNone: 1, readOnly: 0, noRecurse: 1, returnDoesNotAlias: 0, noInline: 0, alwaysInline: 0, noUnwind: 1, mayThrow: 0, hasUnknownCall: 0, mustBeUnreachable: 0)))) ; guid = 3570461062868198843
^8 = gv: (name: "str.17", summaries: (variable: (module: ^0, flags: (linkage: private, visibility: default, notEligibleToImport: 1, live: 0, dsoLocal: 1, canAutoHide: 0, importType: definition), varFlags: (readonly: 1, writeonly: 0, constant: 1)))) ; guid = 3674537065097105755
^9 = gv: (name: ".str.1", summaries: (variable: (module: ^0, flags: (linkage: private, visibility: default, notEligibleToImport: 1, live: 0, dsoLocal: 1, canAutoHide: 0, importType: definition), varFlags: (readonly: 1, writeonly: 0, constant: 1)))) ; guid = 4162905624437313142
^10 = gv: (name: ".str.10", summaries: (variable: (module: ^0, flags: (linkage: private, visibility: default, notEligibleToImport: 1, live: 0, dsoLocal: 1, canAutoHide: 0, importType: definition), varFlags: (readonly: 1, writeonly: 0, constant: 1)))) ; guid = 4644248765473574932
^11 = gv: (name: "__isoc99_scanf") ; guid = 4972326971632665613
^12 = gv: (name: "memo", summaries: (variable: (module: ^0, flags: (linkage: external, visibility: default, notEligibleToImport: 1, live: 0, dsoLocal: 1, canAutoHide: 0, importType: definition), varFlags: (readonly: 1, writeonly: 1, constant: 0)))) ; guid = 5298678913376257237
^13 = gv: (name: "str.19", summaries: (variable: (module: ^0, flags: (linkage: private, visibility: default, notEligibleToImport: 1, live: 0, dsoLocal: 1, canAutoHide: 0, importType: definition), varFlags: (readonly: 1, writeonly: 0, constant: 1)))) ; guid = 5789692345525608196
^14 = gv: (name: "fibonacci", summaries: (function: (module: ^0, flags: (linkage: external, visibility: default, notEligibleToImport: 1, live: 0, dsoLocal: 1, canAutoHide: 0, importType: definition), insts: 15, funcFlags: (readNone: 0, readOnly: 0, noRecurse: 0, returnDoesNotAlias: 0, noInline: 0, alwaysInline: 0, noUnwind: 1, mayThrow: 0, hasUnknownCall: 0, mustBeUnreachable: 0), calls: ((callee: ^5, relbf: 256, tail: 1), (callee: ^4, relbf: 256, tail: 1), (callee: ^25, relbf: 256, tail: 1)), refs: (^12)))) ; guid = 6947095792655537647
^15 = gv: (name: "printf") ; guid = 7383291119112528047
^16 = gv: (name: ".str.12", summaries: (variable: (module: ^0, flags: (linkage: private, visibility: default, notEligibleToImport: 1, live: 0, dsoLocal: 1, canAutoHide: 0, importType: definition), varFlags: (readonly: 1, writeonly: 0, constant: 1)))) ; guid = 8037547672971087919
^17 = gv: (name: "puts") ; guid = 8979701042202144121
^18 = gv: (name: "factorial_iterative", summaries: (function: (module: ^0, flags: (linkage: external, visibility: default, notEligibleToImport: 1, live: 0, dsoLocal: 1, canAutoHide: 0, importType: definition), insts: 45, funcFlags: (readNone: 1, readOnly: 0, noRecurse: 1, returnDoesNotAlias: 0, noInline: 0, alwaysInline: 0, noUnwind: 1, mayThrow: 0, hasUnknownCall: 0, mustBeUnreachable: 0)))) ; guid = 9271727199547709403
^19 = gv: (name: ".str.9", summaries: (variable: (module: ^0, flags: (linkage: private, visibility: default, notEligibleToImport: 1, live: 0, dsoLocal: 1, canAutoHide: 0, importType: definition), varFlags: (readonly: 1, writeonly: 0, constant: 1)))) ; guid = 10797529711175543963
^20 = gv: (name: ".str.8", summaries: (variable: (module: ^0, flags: (linkage: private, visibility: default, notEligibleToImport: 1, live: 0, dsoLocal: 1, canAutoHide: 0, importType: definition), varFlags: (readonly: 1, writeonly: 0, constant: 1)))) ; guid = 12647526809760556658
^21 = gv: (name: "str.20", summaries: (variable: (module: ^0, flags: (linkage: private, visibility: default, notEligibleToImport: 1, live: 0, dsoLocal: 1, canAutoHide: 0, importType: definition), varFlags: (readonly: 1, writeonly: 0, constant: 1)))) ; guid = 13299306947019647461
^22 = gv: (name: ".str", summaries: (variable: (module: ^0, flags: (linkage: private, visibility: default, notEligibleToImport: 1, live: 0, dsoLocal: 1, canAutoHide: 0, importType: definition), varFlags: (readonly: 1, writeonly: 0, constant: 1)))) ; guid = 13853854246998264250
^23 = gv: (name: "str.18", summaries: (variable: (module: ^0, flags: (linkage: private, visibility: default, notEligibleToImport: 1, live: 0, dsoLocal: 1, canAutoHide: 0, importType: definition), varFlags: (readonly: 1, writeonly: 0, constant: 1)))) ; guid = 13878838219271318387
^24 = gv: (name: "fibonacci_iterative", summaries: (function: (module: ^0, flags: (linkage: external, visibility: default, notEligibleToImport: 1, live: 0, dsoLocal: 1, canAutoHide: 0, importType: definition), insts: 39, funcFlags: (readNone: 1, readOnly: 0, noRecurse: 1, returnDoesNotAlias: 0, noInline: 0, alwaysInline: 0, noUnwind: 1, mayThrow: 0, hasUnknownCall: 0, mustBeUnreachable: 0)))) ; guid = 14285019464561813850
^25 = gv: (name: "free") ; guid = 14965618067398077866
^26 = gv: (name: "str", summaries: (variable: (module: ^0, flags: (linkage: private, visibility: default, notEligibleToImport: 1, live: 0, dsoLocal: 1, canAutoHide: 0, importType: definition), varFlags: (readonly: 1, writeonly: 0, constant: 1)))) ; guid = 15093283829526539142
^27 = gv: (name: "main", summaries: (function: (module: ^0, flags: (linkage: external, visibility: default, notEligibleToImport: 1, live: 0, dsoLocal: 1, canAutoHide: 0, importType: definition), insts: 186, funcFlags: (readNone: 0, readOnly: 0, noRecurse: 0, returnDoesNotAlias: 0, noInline: 0, alwaysInline: 0, noUnwind: 1, mayThrow: 0, hasUnknownCall: 0, mustBeUnreachable: 0), calls: ((callee: ^5, relbf: 256, tail: 1), (callee: ^4, relbf: 256, tail: 1), (callee: ^25, relbf: 256, tail: 1), (callee: ^15, relbf: 3275, tail: 1), (callee: ^17, relbf: 1331, tail: 1), (callee: ^11, relbf: 512), (callee: ^2, relbf: 102), (callee: ^28, relbf: 1024)), refs: (^12, ^22, ^9, ^26, ^8, ^23, ^13, ^21, ^6, ^20, ^19, ^10, ^1, ^16, ^32, ^31, ^3)))) ; guid = 15822663052811949562
^28 = gv: (name: "fibonacci_recursive", summaries: (function: (module: ^0, flags: (linkage: external, visibility: default, notEligibleToImport: 1, live: 0, dsoLocal: 1, canAutoHide: 0, importType: definition), insts: 16, funcFlags: (readNone: 1, readOnly: 0, noRecurse: 0, returnDoesNotAlias: 0, noInline: 0, alwaysInline: 0, noUnwind: 1, mayThrow: 0, hasUnknownCall: 0, mustBeUnreachable: 0), calls: ((callee: ^28, relbf: 2560, tail: 1))))) ; guid = 16145704331768065864
^29 = gv: (name: "factorial_tail", summaries: (function: (module: ^0, flags: (linkage: external, visibility: default, notEligibleToImport: 1, live: 0, dsoLocal: 1, canAutoHide: 0, importType: definition), insts: 46, funcFlags: (readNone: 1, readOnly: 0, noRecurse: 1, returnDoesNotAlias: 0, noInline: 0, alwaysInline: 0, noUnwind: 1, mayThrow: 0, hasUnknownCall: 0, mustBeUnreachable: 0)))) ; guid = 16557758678456201975
^30 = gv: (name: "factorial_optimized", summaries: (function: (module: ^0, flags: (linkage: external, visibility: default, notEligibleToImport: 1, live: 0, dsoLocal: 1, canAutoHide: 0, importType: definition), insts: 45, funcFlags: (readNone: 1, readOnly: 0, noRecurse: 1, returnDoesNotAlias: 0, noInline: 0, alwaysInline: 0, noUnwind: 1, mayThrow: 0, hasUnknownCall: 0, mustBeUnreachable: 0)))) ; guid = 16588238421022740881
^31 = gv: (name: ".str.15", summaries: (variable: (module: ^0, flags: (linkage: private, visibility: default, notEligibleToImport: 1, live: 0, dsoLocal: 1, canAutoHide: 0, importType: definition), varFlags: (readonly: 1, writeonly: 0, constant: 1)))) ; guid = 16739303073448881452
^32 = gv: (name: ".str.13", summaries: (variable: (module: ^0, flags: (linkage: private, visibility: default, notEligibleToImport: 1, live: 0, dsoLocal: 1, canAutoHide: 0, importType: definition), varFlags: (readonly: 1, writeonly: 0, constant: 1)))) ; guid = 17490146688062225415
^33 = flags: 8
^34 = blockcount: 0
