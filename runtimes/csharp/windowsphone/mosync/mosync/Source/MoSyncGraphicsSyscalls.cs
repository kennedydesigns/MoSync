using System;
using System.IO;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.GamerServices;
using System.Windows;
using System.Windows.Media.Imaging;
using System.Threading;
using System.Windows.Media;
using System.Windows.Controls;

namespace MoSync
{
    public class GraphicsSyscalls : ISyscallGroup
    {
        public WriteableBitmap mFrontBuffer;
        public WriteableBitmap mBackBuffer;
        public WriteableBitmap mCurrentDrawTarget;
        public int mCurrentDrawTargetIndex = MoSync.Constants.HANDLE_SCREEN;
        private uint mCurrentColor = 0xff000000;
        private System.Windows.Media.Color mCurrentWindowsColor;
        private double mCurrentFontSize = 12;

        public void Init(Syscalls syscalls, Core core, Runtime runtime)
        {
            test_mosync.MainPage mainPage = runtime.GetMainPage();

            mBackBuffer = new WriteableBitmap(
                (int)mainPage.ViewPortContainer.Width,
                (int)mainPage.ViewPortContainer.Height);
            mFrontBuffer = new WriteableBitmap(
                (int)mainPage.ViewPortContainer.Width,
                (int)mainPage.ViewPortContainer.Height);

            mainPage.ViewPort.Source = mFrontBuffer;
            mCurrentDrawTarget = mBackBuffer;

            mCurrentWindowsColor = System.Windows.Media.Color.FromArgb(0xff,
                        (byte)(mCurrentColor >> 16),
                        (byte)(mCurrentColor >> 8),
                        (byte)(mCurrentColor));

            syscalls.maSetColor = delegate(int rgb)
            {
                int oldColor = (int)mCurrentColor;
                mCurrentColor = 0xff000000 | (uint)(rgb & 0xffffff);
                mCurrentWindowsColor = System.Windows.Media.Color.FromArgb(0xff,
                        (byte)(mCurrentColor >> 16),
                        (byte)(mCurrentColor >> 8),
                        (byte)(mCurrentColor));
                return oldColor;
            };

            syscalls.maSetClipRect = delegate(int x, int y, int w, int h)
            {
            };

            syscalls.maGetClipRect = delegate(int cliprect)
            {
            };

            syscalls.maPlot = delegate(int x, int y)
            {
                mCurrentDrawTarget.SetPixel(x, y, (int)mCurrentColor);
            };

            syscalls.maUpdateScreen = delegate()
            {
                System.Array.Copy(mBackBuffer.Pixels, mFrontBuffer.Pixels, mFrontBuffer.PixelWidth * mFrontBuffer.PixelHeight);
                using (AutoResetEvent are = new AutoResetEvent(false))
                {
                    Deployment.Current.Dispatcher.BeginInvoke(() =>
                    {
                        mFrontBuffer.Invalidate();
                        are.Set();
                    });
                    are.WaitOne();
                }
            };

            syscalls.maFillRect = delegate(int x, int y, int w, int h)
            {
                mCurrentDrawTarget.FillRectangle(0, 0, w, h, (int)mCurrentColor);
            };

            syscalls.maLine = delegate(int x1, int y1, int x2, int y2)
            {
                mCurrentDrawTarget.DrawLine(x1, y1, x2, y2, (int)mCurrentColor);
            };

            TextBlock textBlock = new TextBlock();
            textBlock.MaxWidth = 100000.0;
            textBlock.MaxHeight = 100000.0;
            textBlock.FontSize = mCurrentFontSize;

            syscalls.maDrawText = delegate(int left, int top, int str)
            {
                String text = core.GetDataMemory().ReadStringAtAddress(str);
                using (AutoResetEvent are = new AutoResetEvent(false))
                {
                    Deployment.Current.Dispatcher.BeginInvoke(() =>
                    {
                        textBlock.Text = text;
                        textBlock.Foreground = new SolidColorBrush(mCurrentWindowsColor);
                        mCurrentDrawTarget.Render(textBlock, new TranslateTransform() { X = left, Y = top });
                        are.Set();
                    });
                    are.WaitOne();
                }

            };

            syscalls.maGetTextSize = delegate(int str)
            {
                String text = core.GetDataMemory().ReadStringAtAddress(str);
                int textWidth = 0;
                int textHeight = 0;

                using (AutoResetEvent are = new AutoResetEvent(false))
                {
                    Deployment.Current.Dispatcher.BeginInvoke(() =>
                    {
                        textBlock.Text = text;
                        textWidth = (int)textBlock.ActualWidth;
                        textHeight = (int)textBlock.ActualHeight;
                        are.Set();
                    });
                    are.WaitOne();
                }

                return MoSync.Util.CreateExtent(textWidth, textHeight);
            };

            syscalls.maDrawTextW = delegate(int left, int top, int str)
            {
                String text = core.GetDataMemory().ReadWStringAtAddress(str);
                using (AutoResetEvent are = new AutoResetEvent(false))
                {
                    Deployment.Current.Dispatcher.BeginInvoke(() =>
                    {
                        textBlock.Text = text;
                        textBlock.Foreground = new SolidColorBrush(mCurrentWindowsColor);
                        mCurrentDrawTarget.Render(textBlock, new TranslateTransform() { X = left, Y = top });
                        are.Set();
                    });
                    are.WaitOne();
                }

            };

            syscalls.maGetTextSizeW = delegate(int str)
            {
                String text = core.GetDataMemory().ReadWStringAtAddress(str);
                int textWidth = 0;
                int textHeight = 0;

                using (AutoResetEvent are = new AutoResetEvent(false))
                {
                    Deployment.Current.Dispatcher.BeginInvoke(() =>
                    {
                        textBlock.Text = text;
                        textWidth = (int)textBlock.ActualWidth;
                        textHeight = (int)textBlock.ActualHeight;
                        are.Set();
                    });
                    are.WaitOne();
                }

                return MoSync.Util.CreateExtent(textWidth, textHeight);
            };

            syscalls.maFillTriangleFan = delegate(int points, int count)
            {
                int[] newPoints = new int[count * 2];
                for (int i = 0; i < count; i++)
                {
                    newPoints[i * 2 + 0] = core.GetDataMemory().ReadInt32(points + i * 4 + 0);
                    newPoints[i * 2 + 1] = core.GetDataMemory().ReadInt32(points + i * 4 + 1);
                }
                mCurrentDrawTarget.FillPolygon(newPoints, (int)mCurrentColor);
            };

            syscalls.maFillTriangleStrip = delegate(int points, int count)
            {

                int[] xcoords = new int[count];
                int[] ycoords = new int[count];

                for (int i = 0; i < count; i++)
                {
                    xcoords[i] = core.GetDataMemory().ReadInt32(points + i * 4 + 0);
                    ycoords[i] = core.GetDataMemory().ReadInt32(points + i * 4 + 1);
                }

                for (int i = 2; i < count; i++)
                {
                    mCurrentDrawTarget.FillTriangle(
                        xcoords[i - 2], ycoords[i - 2],
                        xcoords[i - 1], ycoords[i - 1],
                        xcoords[i - 0], ycoords[i - 0],
                        (int)mCurrentColor);
                }
            };

            syscalls.maSetDrawTarget = delegate(int drawTarget)
            {
                int oldDrawTarget = mCurrentDrawTargetIndex;
                if (drawTarget == mCurrentDrawTargetIndex) return oldDrawTarget;
                if (drawTarget == MoSync.Constants.HANDLE_SCREEN)
                {
                    mCurrentDrawTarget = mBackBuffer;
                    mCurrentDrawTargetIndex = drawTarget;
                    return oldDrawTarget;
                }

                Resource res = runtime.GetResource(MoSync.Constants.RT_IMAGE, drawTarget);
                mCurrentDrawTarget = (WriteableBitmap)res.GetInternalObject();
                mCurrentDrawTargetIndex = drawTarget;
                return oldDrawTarget;
            };

            syscalls.maGetScrSize = delegate()
            {
                return MoSync.Util.CreateExtent(mBackBuffer.PixelWidth, mBackBuffer.PixelHeight);
            };

            syscalls.maGetImageSize = delegate(int handle)
            {
                Resource res = runtime.GetResource(MoSync.Constants.RT_IMAGE, handle);
                BitmapSource src = (BitmapSource)res.GetInternalObject();
                int w = 0, h = 0;
                using (AutoResetEvent are = new AutoResetEvent(false))
                {
                    Deployment.Current.Dispatcher.BeginInvoke(() =>
                    {
                        w = src.PixelWidth;
                        h = src.PixelHeight;
                        are.Set();
                    });
                    are.WaitOne();
                }
                return MoSync.Util.CreateExtent(w, h);
            };

            syscalls.maDrawImage = delegate(int image, int left, int top)
            {
                Resource res = runtime.GetResource(MoSync.Constants.RT_IMAGE, image);
                WriteableBitmap src = (WriteableBitmap)res.GetInternalObject();
                Rect srcRect = new Rect(0, 0, src.PixelWidth, src.PixelHeight);
                Rect dstRect = new Rect(left, top, src.PixelWidth, src.PixelHeight);
                mCurrentDrawTarget.Blit(dstRect, src, srcRect, WriteableBitmapExtensions.BlendMode.Alpha);
            };

            syscalls.maDrawImageRegion = delegate(int image, int srcRectPtr, int dstPointPtr, int transformMode)
            {
                Resource res = runtime.GetResource(MoSync.Constants.RT_IMAGE, image);
                WriteableBitmap src = (WriteableBitmap)res.GetInternalObject();

                Memory dataMemory = core.GetDataMemory();
                int srcRectX = dataMemory.ReadInt32(srcRectPtr + 0);
                int srcRectY = dataMemory.ReadInt32(srcRectPtr + 4);
                int srcRectW = dataMemory.ReadInt32(srcRectPtr + 8);
                int srcRectH = dataMemory.ReadInt32(srcRectPtr + 12);
                int dstPointX = dataMemory.ReadInt32(dstPointPtr + 0);
                int dstPointY = dataMemory.ReadInt32(dstPointPtr + 4);

                Rect srcRect = new Rect(srcRectX, srcRectY, srcRectW, srcRectH);
                Rect dstRect = new Rect(dstPointX, dstPointY, srcRectW, srcRectH);
                mCurrentDrawTarget.Blit(dstRect, src, srcRect, WriteableBitmapExtensions.BlendMode.Alpha);
            };

            syscalls.maCreateDrawableImage = delegate(int placeholder, int width, int height)
            {
                Resource res = runtime.GetResource(MoSync.Constants.RT_PLACEHOLDER, placeholder);
                res.SetResourceType(MoSync.Constants.RT_IMAGE);
                WriteableBitmap bitmap = null;
                using (AutoResetEvent are = new AutoResetEvent(false))
                {
                    Deployment.Current.Dispatcher.BeginInvoke(() =>
                    {
                        bitmap = new WriteableBitmap(width, height);
                        are.Set();
                    });
                    are.WaitOne();
                }


                if (bitmap == null) return MoSync.Constants.RES_OUT_OF_MEMORY;
                res.SetInternalObject(bitmap);
                return MoSync.Constants.RES_OK;
            };
        }
    }
}

